#pragma once

#include <QWidget>
#include <QtCharts>

QT_BEGIN_NAMESPACE
class QComboBox;
class QPushButton;
QT_END_NAMESPACE

class PollutantOverviewPage : public QWidget
{
    Q_OBJECT

public:
    PollutantOverviewPage(QWidget *parent = nullptr);

signals:
    void returnToDashboard();

private:
    void setupUI();
    void setupChart();

    // UI Elements
    QComboBox* searchCombo;
    QPushButton* searchButton;
    QChartView* chartView;
};