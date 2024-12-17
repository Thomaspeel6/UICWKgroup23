#include "POPsPage.hpp"
#include <QtWidgets>
#include <QtCharts>
#include <QToolTip>
#include <QMouseEvent>

POPsPage::POPsPage(QTabWidget* tabWidget, QWidget* parent)
    : QWidget(parent), tabWidget(tabWidget)
{
    createChart();
    arrangeWidgets();
    setupConnections();
}

void POPsPage::createChart()
{
    chart = new QChart();
    lineSeries = new QLineSeries();

    lineSeries->append(0, 5);
    lineSeries->append(1, 15);
    lineSeries->append(2, 25);
    lineSeries->append(3, 10);
    lineSeries->append(4, 20);

    lineSeries->setName("sample Data");

    chart->addSeries(lineSeries);
    chart->createDefaultAxes();

    chart->setTitle("Persistent Organic Pollutants");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void POPsPage::arrangeWidgets()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    setLayout(layout);
}

void POPsPage::setupConnections()
{
    connect(lineSeries, &QLineSeries::hovered, this, &POPsPage::showTooltip);
}

void POPsPage::showTooltip(const QPointF &point, bool state)
{
    if (state) {
        QToolTip::showText(
            QCursor::pos(),
            QString("X: %1\nY: %2").arg(point.x()).arg(point.y()),
            this
        );
    } else {
        QToolTip::hideText();
    }
}