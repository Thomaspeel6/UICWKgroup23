#ifndef POPS_PAGE_HPP
#define POPS_PAGE_HPP

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts>
#include <QDateTime>
#include <QLineEdit>
#include <QCheckBox>
#include <QMap>
#include <QWidget>
#include <QMainWindow>
#include "model.hpp"

// Forward refs.
class QTabWidget;
class QVBoxLayout;
class QHBoxLayout;
class QChartView;
class waterQualityModel;


static QStringList popDeterminands {
    "EndosulphanA",
    "EndosulphanB",
    "PCB Con 028",
    "PCB Con 052",
    "PCB Con 180",
    "PCB Con 105"
};

class POPsPage : public QWidget
{
    Q_OBJECT

public:
    explicit POPsPage(QTabWidget* tabWidget, waterQualityModel* model, QWidget* parent = nullptr);
    void updateChart();
    void loadComplianceThresholds(const QString& filePath);

private:
    void createChart();
    void arrangeWidgets();
    void setupConnections();
    void createFiltersUI();

    // Pointers for widgets.
    QChartView *chartView;
    QChart *chart;
    
    QTabWidget *tabWidget;
    waterQualityModel *model;

    QMap<QString, QLineSeries*> seriesMap;
    QMap<QString, QCheckBox*> checkBoxMap;
    QMap<QString, double> complianceThresholdMap;

private slots:
    void showTooltip(const QPointF &point, bool state);
    void filterDeterminand(const QString &label, bool visible);
};

#endif 
