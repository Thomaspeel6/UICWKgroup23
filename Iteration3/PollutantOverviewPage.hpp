#pragma once

#include <QWidget>
#include <QtCharts>
#include "model.hpp"

class QComboBox;
class QPushButton;
class QListWidget;
class QChartView;

struct ProcessedPollutantData {
    QString dateTime;
    double result;
    QString samplingPoint;
    QString materialType;
    QString purpose;
    int easting;
    int northing;
    bool isCompliance;
    QString unit;
};

class PollutantOverviewPage : public QWidget
{
    Q_OBJECT

public:
    explicit PollutantOverviewPage(waterQualityModel* model, QWidget *parent = nullptr);
    void loadComplianceThresholds(const QString& filePath);
    public slots:
        void handleDataUpdate(const QModelIndex& topLeft, const QModelIndex& bottomRight, const QList<int>& roles = QList<int>());
    void retranslateUi();

private:
    void setupUI();
    void setupChart(const QString& pollutantName = QString());
    void connectSignals();
    void updateSamplePoints(const QString& pollutantName);
    

    QStringList getAllPollutants() const;
    QStringList getSamplePoints(const QString& pollutantName) const;
    void updateLists();
    QVector<ProcessedPollutantData> processData(const QString& pollutantName, const QStringList& selectedSamplePoints);
    void handleChartPointClick(QScatterSeries* series, const QPointF& point);

    QMap<QString, double> complianceThreshold;

    QComboBox* searchCombo;
    QComboBox* samplePointList;
    QPushButton* searchButton;
    QChartView* chartView;

    QScrollArea* scrollArea;
    QWidget* contentWidget;

    waterQualityModel* model;
    QHash<QString, QVector<ProcessedPollutantData>> dataCache;
    QString tooltipFormat;
};