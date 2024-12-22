#include "POPsPage.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCursor>
#include <QDateTime>
#include <QtWidgets>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QToolTip>
#include <QMouseEvent>



POPsPage::POPsPage(QTabWidget* tabWidget, waterQualityModel* model, QWidget* parent)
    : QWidget(parent), tabWidget(tabWidget), model(model), chart(nullptr), chartView(nullptr)
{
    createChart();
    createFiltersUI();
    arrangeWidgets();
    setupConnections();
}

void POPsPage::createChart()
{
    // Create default chart
    chart = new QChart();
    chart->setTitle(tr("Persistent Organic Pollutants"));

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void POPsPage::createFiltersUI()
{
    // For each known POP determinand, create a checkbox
    for (const QString& pop : popDeterminands) {
        QCheckBox* box = new QCheckBox(pop, this);
        box->setChecked(true);

        // Connect the toggled signal
        connect(box, &QCheckBox::toggled, this, [=](bool checked) {
            filterDeterminand(pop, checked);
        });

        checkBoxMap[pop] = box;
    }
}

void POPsPage::arrangeWidgets()
{
    // Arrange check box and chart layout
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* filterLayout = new QHBoxLayout;
    for (auto it = checkBoxMap.begin(); it != checkBoxMap.end(); ++it) {
        filterLayout->addWidget(it.value());
    }
    filterLayout->addStretch();

    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(chartView); 
    setLayout(mainLayout);
}

void POPsPage::setupConnections() {
}

void POPsPage::loadComplianceThresholds(const QString& filePath)
{
    // Open the CSV
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << tr("[POPsPage] Cannot open threshold CSV:") << filePath;
        return;
    }

    // Clear existing threshold map
    complianceThresholdMap.clear();

    // Read each line
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QStringList parts = line.split(",");
        if (parts.size() != 2) {
            qWarning() << tr("[POPsPage] Skipping invalid threshold line:") << line;
            continue;
        }

        QString label = parts[0].trimmed();
        QString valStr = parts[1].trimmed();

        bool ok = false;
        double thresholdVal = valStr.toDouble(&ok);
        if (!ok) {
            qWarning() << tr("[POPsPage] Invalid threshold number in line:") << line;
            continue;
        }

        // Store in the map
        complianceThresholdMap[label] = thresholdVal;
    }

    file.close();
    qDebug() << tr("[POPsPage] Loaded") << complianceThresholdMap.size()
             << tr("threshold entries from") << filePath;
}

void POPsPage::updateChart()
{
    if (!model || !model->hasData()) {
        chart->removeAllSeries();
        return;
    }

    // Build a map from determinand label
    QMap<QString, QVector<QPair<QDateTime, double>>> popDataMap;
    const auto& dataVector = model->getDataset().getData();

    for (auto& entry : dataVector) {
        QString label = QString::fromStdString(entry.getDeterminandLabel());
        // Only process if label is in popDeterminands
        if (popDeterminands.contains(label, Qt::CaseInsensitive)) {
            QString resultStr = QString::fromStdString(entry.getResult());
            if (resultStr.startsWith("<")) {
                // handle below detection limit
                resultStr.remove(0,1);
            }
            double val = resultStr.toDouble();

            QDateTime dt = QDateTime::fromString(
                QString::fromStdString(entry.getSampleDateTime()),
                Qt::ISODate
            );
            if (!dt.isValid()) {
                continue;
            }
            popDataMap[label].append({dt, val});
        }
    }

    // Sort each labels data by datetime
    for (auto it = popDataMap.begin(); it != popDataMap.end(); ++it) {
        auto &vec = it.value();
        std::sort(vec.begin(), vec.end(),
                  [](auto &a, auto &b){ return a.first < b.first; });
    }

    // Clear old series from the chart
    chart->removeAllSeries();
    seriesMap.clear();

    // Create new axes each time
    QDateTimeAxis* xAxis = new QDateTimeAxis;
    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText(tr("Date"));
    chart->addAxis(xAxis, Qt::AlignBottom);

    QValueAxis* yAxis = new QValueAxis;
    yAxis->setTitleText(tr("Concentration (µg/L)"));
    chart->addAxis(yAxis, Qt::AlignLeft);

    // For each determinand, create the main data series
    for (auto it = popDataMap.begin(); it != popDataMap.end(); ++it) {
        const QString &label = it.key();
        const auto &points = it.value();
        if (points.isEmpty())
            continue;

        // Create the main data series
        QLineSeries* mainSeries = new QLineSeries();
        mainSeries->setName(label);

        QDateTime earliest = points.first().first;
        QDateTime latest   = points.last().first;

        for (auto &p : points) {
            qint64 xVal = p.first.toMSecsSinceEpoch();
            double yVal = p.second;
            mainSeries->append(xVal, yVal);
        }

        // Add the main data series to the chart
        chart->addSeries(mainSeries);
        mainSeries->attachAxis(xAxis);
        mainSeries->attachAxis(yAxis);

        // Connect for tooltips on hover
        connect(mainSeries, &QLineSeries::hovered, this, &POPsPage::showTooltip);

        // Store in seriesMap for filtering
        seriesMap[label] = mainSeries;

        // If we have a threshold, add it to chart
        if (complianceThresholdMap.contains(label)) {
            double thresholdVal = complianceThresholdMap[label];
            qDebug() << tr("Value:") << thresholdVal;

            QLineSeries* thresholdSeries = new QLineSeries();
            thresholdSeries->append(earliest.toMSecsSinceEpoch(), thresholdVal);
            thresholdSeries->append(latest.toMSecsSinceEpoch(),  thresholdVal);

            // Match the color of the mainSeries
            QColor mainColor = mainSeries->color();
            QPen dashedPen(mainColor);
            dashedPen.setStyle(Qt::DashLine);
            dashedPen.setWidth(2);
            thresholdSeries->setPen(dashedPen);

            thresholdSeries->setName(label + tr(" Threshold"));

            chart->addSeries(thresholdSeries);
            thresholdSeries->attachAxis(xAxis);
            thresholdSeries->attachAxis(yAxis);

            QDateTime earliest = points.first().first;
            QDateTime latest = points.last().first;
            qDebug() << tr("Earliest:") << earliest << tr("Latest:") << latest;
        }
    }

    // Apply the checkbox filter
    for (auto it = seriesMap.begin(); it != seriesMap.end(); ++it) {
        QString label = it.key();
        QLineSeries* s = it.value();

        if (checkBoxMap.contains(label) && !checkBoxMap[label]->isChecked()) {
            s->setVisible(false);
        }
    }

    chart->setTitle(tr("Multiple POPs Over Time with Thresholds"));

}


void POPsPage::filterDeterminand(const QString &label, bool visible) {
    // Toggle visibility
    if (seriesMap.contains(label)) {
        QLineSeries* s = seriesMap[label];
        s->setVisible(visible);
    }
}

void POPsPage::showTooltip(const QPointF &point, bool state)
{
    // Show date and result values on hover
    if (state) {
        qint64 xVal = (qint64)point.x();
        QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(xVal);
        QString msg = QString(tr("Date: %1\nValue: %2"))
                .arg(dateTime.toString("yyyy-MM-dd"))
                .arg(point.y());
        QToolTip::showText(QCursor::pos(), msg, this);
    } else {
        QToolTip::hideText();
    }
}