#include "FluorinatedCompoundsPage.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QMessageBox>
#include <QToolTip>
#include <QtCharts/QChartView>

FluorinatedCompoundsPage::FluorinatedCompoundsPage(QWidget* parent)
        : QWidget(parent), chartView(new QChartView(this)), pollutantSelector(new QComboBox(this)) {
    setupUI();
    setupChart();
    connectSignals();
}

void FluorinatedCompoundsPage::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Fluorinated Compounds", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font: bold 18px; margin: 10px;");
    mainLayout->addWidget(titleLabel);

    QHBoxLayout* topLayout = new QHBoxLayout();
    pollutantSelector->addItem("PFAS");
    pollutantSelector->setMinimumWidth(200);

    topLayout->addWidget(pollutantSelector);
    topLayout->addStretch();
    mainLayout->addLayout(topLayout);

    chartView->setRenderHint(QPainter::Antialiasing);
    mainLayout->addWidget(chartView);

    setLayout(mainLayout);
}

void FluorinatedCompoundsPage::setupChart() {
    QChart* chart = new QChart();
    chart->setTitle("Fluorinated Compounds Over Time");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chartView->setChart(chart);
}

void FluorinatedCompoundsPage::connectSignals() {
    connect(pollutantSelector, &QComboBox::currentTextChanged, this, &FluorinatedCompoundsPage::updateChart);
}

void FluorinatedCompoundsPage::updateChart(const QString& pollutantName) {
    // Dummy Data for Example
    QList<QPair<QDateTime, double>> data = {

    };

    if (data.isEmpty()) {
        QMessageBox::warning(this, "No Data", "No data available for the selected pollutant.");
        return;
    }

    QChart* chart = new QChart();
    chart->setTitle("Levels of " + pollutantName + " Over Time");

    QLineSeries* series = new QLineSeries();
    QDateTimeAxis* xAxis = new QDateTimeAxis();
    QValueAxis* yAxis = new QValueAxis();

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();

    for (const auto& point : data) {
        series->append(point.first.toMSecsSinceEpoch(), point.second);
        minY = std::min(minY, point.second);
        maxY = std::max(maxY, point.second);
    }

    xAxis->setFormat("yyyy-MM-dd");
    xAxis->setTitleText("Date");
    yAxis->setRange(minY * 0.9, maxY * 1.1);
    yAxis->setTitleText("Concentration (µg/L)");

    chart->addSeries(series);
    chart->addAxis(xAxis, Qt::AlignBottom);
    chart->addAxis(yAxis, Qt::AlignLeft);
    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    chart->legend()->hide();
    chartView->setChart(chart);

    connect(series, &QLineSeries::hovered, this, [this, pollutantName](const QPointF& point, bool state) {
        if (state) {
            QToolTip::showText(QCursor::pos(),
                               QString("Pollutant: %1\nDate: %2\nConcentration: %3 µg/L")
                                       .arg(pollutantName)
                                       .arg(QDateTime::fromMSecsSinceEpoch(qint64(point.x())).toString("yyyy-MM-dd"))
                                       .arg(point.y(), 0, 'f', 2),
                               chartView);
        }
    });
}
