#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QMap>
#include <QVariant>
#include "model.hpp"
#include <QScrollArea>
#include <QGridLayout>

class ComplianceDashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit ComplianceDashboardPage(waterQualityModel* model, QWidget* parent = nullptr);

    void loadComplianceThresholds(const QString& filePath); 

private:

    QComboBox* locationFilter;
    QComboBox* pollutantFilter;
    QComboBox* complianceStatusFilter;
    QPushButton* applyFilterButton;
    QPushButton* nextPageButton;
    QPushButton* previousPageButton;
    QScrollArea* scrollArea;
    QWidget* cardContainer;
    QGridLayout* gridLayout;



    waterQualityModel* model;
    QMap<QString, double> complianceThresholds; 
    QList<QMap<QString, QVariant>> filteredData; 
    int currentPage;
    const int itemsPerPage = 12;


    void populateFilters();
    void applyFilters();
    void updatePagination();
private slots:
    void onApplyFilters();
    void onNextPage();
    void onPreviousPage(); 
};
