#include <QtWidgets>
#include "PollutantOverviewPage.hpp"

PollutantOverviewPage::PollutantOverviewPage(waterQualityModel* model, QWidget *parent)
    : QWidget(parent)
    , model(model)
    , searchCombo(nullptr)
    , searchButton(nullptr)
    , chartView(nullptr)
{
    setupUI();
    setupChart();
    connectSignals();
}

void PollutantOverviewPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // head button
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    QStringList buttonTexts = {"Pollutant Overview", "POPs", "Litter Indicators",
                              "Fluorinated Compounds", "Compliance", "Geographic Hotspots"};
    
    for (const QString& text : buttonTexts) {
        QPushButton* button = new QPushButton(text);
        button->setFixedHeight(40);
        button->setStyleSheet(
            "QPushButton {"
            "   background-color: #f8f9fa;"
            "   border: 1px solid #dee2e6;"
            "   border-radius: 5px;"
            "   padding: 5px 15px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #e9ecef;"
            "}"
        );
        if (text == "Pollutant Overview") {
            connect(button, &QPushButton::clicked, this, &PollutantOverviewPage::returnToDashboard);
        }
        buttonsLayout->addWidget(button);
    }
    mainLayout->addLayout(buttonsLayout);

    // search
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchCombo = new QComboBox();
    searchCombo->setEditable(true);
    searchCombo->setPlaceholderText("Search pollutants");
    searchCombo->setMinimumWidth(300);
    searchCombo->addItems(model->getAllPollutants());
    searchCombo->setStyleSheet(
        "QComboBox {"
        "   padding: 8px;"
        "   border: 1px solid #ced4da;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   min-width: 200px;"
        "}"
    );
    
    searchButton = new QPushButton("Search");
    searchButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #28a745;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   padding: 8px 15px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #218838;"
        "}"
    );
    
    searchLayout->addWidget(searchCombo);
    searchLayout->addWidget(searchButton);
    searchLayout->addStretch();
    mainLayout->addLayout(searchLayout);

    // chart view
    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(400);
    mainLayout->addWidget(chartView);
}

void PollutantOverviewPage::setupChart()
{
    QChart* chart = new QChart();
    chart->setTitle("Pollutant Levels Over Time");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chartView->setChart(chart);
}

void PollutantOverviewPage::updateChart(const QString& pollutantName)
{
    auto data = model->getTimeSeriesData(pollutantName);

    if (data.empty()) {
        QMessageBox::warning(this, "No Data", 
            "No data available for selected pollutant: " + pollutantName);
        return;
    }
    
    // data sort
    std::sort(data.begin(), data.end(), 
        [](const auto& a, const auto& b) {
            return QDateTime::fromString(a.first, Qt::ISODate) < 
                   QDateTime::fromString(b.first, Qt::ISODate);
        });
    
    QChart* chart = new QChart();
    chart->setTitle("Pollutant Levels Over Time: " + pollutantName);
    
    QLineSeries* series = new QLineSeries();
    QDateTimeAxis* axisX = new QDateTimeAxis();
    QValueAxis* axisY = new QValueAxis();
    
    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();
    
    for (const auto& point : data) {
        QDateTime dateTime = QDateTime::fromString(point.first, Qt::ISODate);
        double value = point.second;
        series->append(dateTime.toMSecsSinceEpoch(), value);
        
        minY = std::min(minY, value);
        maxY = std::max(maxY, value);
    }
    
    // y
    double range = maxY - minY;
    axisY->setRange(minY - range * 0.1, maxY + range * 0.1);
    axisY->setLabelFormat("%.4f");
    axisY->setTickCount(5);

    // click point
    connect(series, &QLineSeries::clicked, this, [this, series, pollutantName](const QPointF &point) {
        int index = -1;
        qreal minDistance = std::numeric_limits<qreal>::max();
        const auto points = series->points();
        
        for (int i = 0; i < points.size(); ++i) {
            qreal distance = std::abs(points[i].x() - point.x());
            if (distance < minDistance) {
                minDistance = distance;
                index = i;
            }
        }
        
        if (index >= 0) {
            QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(qint64(points[index].x()));
            QString tooltip = model->getDataPointDetails(pollutantName, dateTime.toString(Qt::ISODate));
            QToolTip::showText(QCursor::pos(), tooltip, chartView, QRect(), 5000);
        }
    });
    
    // coordinatiion
    chart->addSeries(series);
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    
    // axis
    axisX->setTitleText("Time");
    axisY->setTitleText("Result");
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTickCount(6);
    
    // chart
    chart->setTheme(QChart::ChartThemeLight);
    chart->legend()->hide();
    
    // point
    series->setPointsVisible(true);
    series->setMarkerSize(10);
    series->setPen(QPen(Qt::blue, 2));
    
    chartView->setChart(chart);
}

void PollutantOverviewPage::connectSignals()
{
    connect(searchButton, &QPushButton::clicked, this, [this]() {
        QString pollutantName = searchCombo->currentText();
        if (!pollutantName.isEmpty()) {
            updateChart(pollutantName);
        }
    });
    
    connect(searchCombo, &QComboBox::editTextChanged, this, [this](const QString& text) {
        if (text.isEmpty()) return;
        auto completions = model->getAllPollutants().filter(text, Qt::CaseInsensitive);
        searchCombo->clear();
        searchCombo->addItems(completions);
    });
}

void PollutantOverviewPage::updateData()
{
    searchCombo->clear();
    searchCombo->addItems(model->getAllPollutants());
    setupChart();
}