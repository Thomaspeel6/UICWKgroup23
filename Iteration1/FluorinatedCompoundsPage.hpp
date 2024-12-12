#pragma once

#include <QWidget>
#include <QtCharts>
#include "model.hpp"


class QChartView;
class QPushButton;
class QComboBox;


class FluorinatedCompoundsPage : public QWidget {


public:
    explicit FluorinatedCompoundsPage(QWidget* parent = nullptr);

private:
    void setupUI();
    void setupChart();
    void connectSignals();

    QChartView* chartView;
    QComboBox* pollutantSelector;
    QPushButton* backButton;
    waterQualityModel* model;


signals:
    void returnToDashboard();

public slots:
    void updateChart(const QString& pollutantName);
};
