#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QMap>
#include <QVariant>
#include <QScrollArea>
#include <QGridLayout>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QCategoryAxis>
#include "model.hpp"

class FluorinatedCompoundsPage : public QWidget
{
    Q_OBJECT

public:
    explicit FluorinatedCompoundsPage(waterQualityModel* model, QWidget* parent = nullptr);

    void loadFluorinatedThresholds(const QString& filePath);
    void retranslateUi();

private:
    QComboBox* fluorineLocationFilter;
    QComboBox* fluorinePollutantFilter;
    QPushButton* applyFluorineFilterButton;
    QScrollArea* fluorineScrollArea;
    QWidget* fluorineCardContainer;
    QGridLayout* fluorineGridLayout;

    QLabel* pollutantLevelLabel;
    QLabel* complianceIndicator;

    waterQualityModel* model;
    QMap<QString, double> fluorineThresholds;
    QVector<QPointF> fluorineFilteredData;


    QChart* fluorineChart = nullptr;
    QLineSeries* fluorineSeries = nullptr;
    QChartView* fluorineChartView = nullptr;


    QValueAxis* yAxis = nullptr;
    QCategoryAxis* xAxis = nullptr;

    void populateFluorineFilters();
    void updateFluorineChart();
    void showTooltip(const QPointF& point, bool state);

    private slots:
        void onApplyFluorineFilters();
};
