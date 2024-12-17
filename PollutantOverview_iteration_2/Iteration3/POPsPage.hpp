#ifndef POPS_PAGE_HPP
#define POPS_PAGE_HPP

#include <QtCharts>
#include <QWidget>
#include <QMainWindow>

// Forward refs.
class QChartView;
class QChart;
class QLineSeries;

class POPsPage : public QWidget
{
    Q_OBJECT

public:
    explicit POPsPage(QTabWidget* tabWidget, QWidget* parent = nullptr);

private:
    void createChart();
    void arrangeWidgets();
    void setupConnections();

    // Pointers for widgets.
    QChartView *chartView;
    QChart *chart;
    QLineSeries *lineSeries;
    QTabWidget *tabWidget;

private slots:
    void showTooltip(const QPointF &point, bool state);
};

#endif 
