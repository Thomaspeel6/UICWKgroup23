#pragma once

#include <QWidget>
#include <QtCharts>
#include "model.hpp"

QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

class PollutantOverviewPage : public QWidget
{
    Q_OBJECT

public:
    PollutantOverviewPage(waterQualityModel* model, QWidget *parent = nullptr);
    void updateData();

signals:
    void returnToDashboard();

private:
    void setupUI();
    void setupChart();
    void connectSignals();
    void updateChart(const QString& pollutantName);

    // UI Elements
    QComboBox* searchCombo;
    QPushButton* searchButton;
    QChartView* chartView;
    
    // Data
    waterQualityModel* model;
};