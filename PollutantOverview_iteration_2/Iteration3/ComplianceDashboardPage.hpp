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

    void loadComplianceThresholds(const QString& filePath); // Load thresholds from a CSV

private:
    // UI Components
    QComboBox* locationFilter;
    QComboBox* pollutantFilter;
    QComboBox* complianceStatusFilter;
    QPushButton* applyFilterButton;
    QPushButton* nextPageButton;
    QPushButton* previousPageButton;
    QScrollArea* scrollArea;      // Holds the scrollable content
    QWidget* cardContainer;       // Container for cards
    QGridLayout* gridLayout;      // Layout to arrange cards in a grid



    // Data
    waterQualityModel* model;              // Pointer to the real data model
    QMap<QString, double> complianceThresholds; // Pollutant thresholds
    QList<QMap<QString, QVariant>> filteredData; // Filtered records for pagination
    int currentPage;                       // Current page number
    const int itemsPerPage = 12;           // Items per page

    // Private Methods
    void populateFilters();                // Populate filters dynamically
    void applyFilters();                   // Apply filters and prepare data for pagination
    void updatePagination();               // Update displayed cards based on the current page

private slots:
    void onApplyFilters();                 // Slot for the Apply Filters button
    void onNextPage();                     // Slot for the Next Page button
    void onPreviousPage();                 // Slot for the Previous Page button
};
