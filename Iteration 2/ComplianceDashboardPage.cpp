#include "ComplianceDashboardPage.hpp"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QComboBox>
#include <QListWidgetItem>
#include <QPalette>
#include <QMouseEvent>

ComplianceDashboardPage::ComplianceDashboardPage(QWidget* parent)
    : QWidget(parent)
{
    // Initialize filters
    locationFilter = new QComboBox(this);
    pollutantFilter = new QComboBox(this);
    complianceStatusFilter = new QComboBox(this);

    // Dummy filter options
    locationFilter->addItem("All Locations");
    locationFilter->addItem("Location 1");
    locationFilter->addItem("Location 2");

    pollutantFilter->addItem("All Pollutants");
    pollutantFilter->addItem("Pollutant 1");
    pollutantFilter->addItem("Pollutant 2");
    pollutantFilter->addItem("Pollutant 3");

    complianceStatusFilter->addItem("All Status");
    complianceStatusFilter->addItem("Compliant");
    complianceStatusFilter->addItem("Non-Compliant");

    // Apply Filter Button
    applyFilterButton = new QPushButton("Apply Filters", this);

    // Compliance Card List
    cardListWidget = new QListWidget(this);

    // Progress Bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setVisible(false);  // Hide progress bar by default

    // Layout
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(locationFilter);
    layout->addWidget(pollutantFilter);
    layout->addWidget(complianceStatusFilter);
    layout->addWidget(applyFilterButton);
    layout->addWidget(cardListWidget);
    layout->addWidget(progressBar);

    setLayout(layout);

    // Connect buttons to slots
    connect(applyFilterButton, &QPushButton::clicked, this, &ComplianceDashboardPage::applyFilters);

    // Add dummy compliance cards
    addComplianceCards();  // Initially add all cards
}

void ComplianceDashboardPage::addComplianceCards()
{
    qDebug() << "addComplianceCards called.";
    cardListWidget->clear();  // Clear existing cards

    pollutants = {"Pollutant 1", "Pollutant 2", "Pollutant 3"};
    compliancePercentages = {97.5, 92.0, 85.0};  // Example compliance percentages
    locations = {"Location 1", "Location 2", "Location 1"};  // Example locations

    QString selectedLocation = locationFilter->currentText();
    QString selectedPollutant = pollutantFilter->currentText();
    QString selectedStatus = complianceStatusFilter->currentText();

    qDebug() << "Selected Location:" << selectedLocation;
    qDebug() << "Selected Pollutant:" << selectedPollutant;
    qDebug() << "Selected Status:" << selectedStatus;

    for (int i = 0; i < pollutants.size(); ++i) {
        // Filtering logic
        bool locationMatch = (selectedLocation == "All Locations" || locations[i] == selectedLocation);
        bool pollutantMatch = (selectedPollutant == "All Pollutants" || pollutants[i] == selectedPollutant);
        bool statusMatch = (selectedStatus == "All Status" ||
                            (selectedStatus == "Compliant" && compliancePercentages[i] >= 90) ||
                            (selectedStatus == "Non-Compliant" && compliancePercentages[i] < 90));

        qDebug() << "Card" << i << ":" << pollutants[i]
                 << "Location Match:" << locationMatch
                 << "Pollutant Match:" << pollutantMatch
                 << "Status Match:" << statusMatch;

        // If the card matches all filters, display it
        if (locationMatch && pollutantMatch && statusMatch) {
            QWidget* card = new QWidget(this);
            QVBoxLayout* cardLayout = new QVBoxLayout(card);
            QLabel* nameLabel = new QLabel(pollutants[i], this);
            QLabel* statusLabel = new QLabel(QString("Compliance: %1%").arg(compliancePercentages[i]), this);

            // Set background color
            QString color = (compliancePercentages[i] >= 95) ? "green"
                           : (compliancePercentages[i] >= 90) ? "orange"
                           : "red";
            card->setStyleSheet(QString("background-color: %1; border-radius: 5px; margin: 5px;").arg(color));

            cardLayout->addWidget(nameLabel);
            cardLayout->addWidget(statusLabel);
            card->setLayout(cardLayout);

            QListWidgetItem* item = new QListWidgetItem(cardListWidget);
            item->setSizeHint(card->sizeHint());
            cardListWidget->setItemWidget(item, card);

            qDebug() << "Card added for pollutant:" << pollutants[i];
        }else{

        }
    }

    qDebug() << "Total cards in list:" << cardListWidget->count();
}


// Function to determine the compliance color based on the percentage
QColor ComplianceDashboardPage::getComplianceColor(double percentage) {
    if (percentage >= 95) {
        return QColor("green");  // Green for > 95% compliant
    } else if (percentage >= 90) {
        return QColor("orange");  // Orange for 90% - 95% compliant
    } else {
        return QColor("red");  // Red for less than 90% compliant
    }
}

void ComplianceDashboardPage::applyFilters()
{
    // Apply the filters and update the list of compliance cards
    addComplianceCards();
}

void ComplianceDashboardPage::showComplianceDetails(const QString& pollutantName)
{
    // Show detailed information for non-compliant pollutant (dummy implementation)
    QMessageBox::information(this, "Compliance Details",
                             QString("Details for %1:\nPossible causes, historical trends, etc.")
                             .arg(pollutantName));
}
