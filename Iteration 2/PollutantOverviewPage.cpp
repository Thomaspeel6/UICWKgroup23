#include <QtWidgets>
#include "PollutantOverviewPage.hpp"

PollutantOverviewPage::PollutantOverviewPage(QWidget *parent)
    : QWidget(parent)
    , searchCombo(nullptr)
    , searchButton(nullptr)
    , chartView(nullptr)
{
    setupUI();
    setupChart();
}

void PollutantOverviewPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    

    // search area
    QHBoxLayout* searchLayout = new QHBoxLayout();
    searchCombo = new QComboBox();
    searchCombo->setEditable(true);
    searchCombo->setPlaceholderText("Search pollutants");
    searchCombo->setMinimumWidth(300);
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
    
    QLineSeries* series = new QLineSeries();
    
    // Add two sample data points
    QDateTime startDate = QDateTime::currentDateTime().addMonths(-1);
    QDateTime endDate = QDateTime::currentDateTime();
    
    series->append(startDate.toMSecsSinceEpoch(), 25.0);
    series->append(endDate.toMSecsSinceEpoch(), 75.0);
    
    series->setPointsVisible(true);
    series->setMarkerSize(10);
    series->setPen(QPen(Qt::blue, 2));
    
    chart->addSeries(series);
    
    // Setup axes
    QDateTimeAxis* axisX = new QDateTimeAxis();
    QValueAxis* axisY = new QValueAxis();
    
    axisX->setTitleText("Time");
    axisY->setTitleText("Result");
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTickCount(6);
    
    axisY->setRange(0, 100);
    axisY->setTickCount(5);
    
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    
    chart->setTheme(QChart::ChartThemeLight);
    chart->legend()->hide();
    
    chartView->setChart(chart);
}