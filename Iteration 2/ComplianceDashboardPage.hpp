#pragma once

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>
#include <QProgressBar>
#include "model.hpp"  // Assuming you still need the model for data

class ComplianceDashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit ComplianceDashboardPage(QWidget* parent = nullptr);

private:
    QComboBox* locationFilter;
    QComboBox* pollutantFilter;
    QComboBox* complianceStatusFilter;
    QPushButton* applyFilterButton;
    QListWidget* cardListWidget;
     
    QProgressBar* progressBar;

    // Function to add compliance cards with traffic light system
    void addComplianceCards();

    // Function to determine compliance color based on percentage
    QColor getComplianceColor(double percentage);

    // Dummy data for filtering
    QStringList pollutants;
    QList<double> compliancePercentages;
    QStringList locations;

private slots:
    void applyFilters();
    void showComplianceDetails(const QString& pollutantName);
};
