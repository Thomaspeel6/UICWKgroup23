#include "ComplianceDashboardPage.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QScrollArea>


// Constructor
ComplianceDashboardPage::ComplianceDashboardPage(waterQualityModel* model, QWidget* parent)
    : QWidget(parent), model(model), currentPage(0)
{
    // Initialize UI components
    locationFilter = new QComboBox(this);
    pollutantFilter = new QComboBox(this);
    complianceStatusFilter = new QComboBox(this);
    applyFilterButton = new QPushButton("Apply Filters", this);
    
    // Create horizontal layout for Previous and Next buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    previousPageButton = new QPushButton("Previous", this);
    nextPageButton = new QPushButton("Next", this);

    // Add buttons to the horizontal layout
    buttonLayout->addWidget(previousPageButton);
    buttonLayout->addWidget(nextPageButton);

    // Align buttons to center or right (optional)
    buttonLayout->setAlignment(Qt::AlignCenter);


    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    cardContainer = new QWidget();
    gridLayout = new QGridLayout(cardContainer);

    scrollArea->setWidget(cardContainer);

    // Create layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(locationFilter);
    layout->addWidget(pollutantFilter);
    layout->addWidget(complianceStatusFilter);
    layout->addWidget(applyFilterButton);
    layout->addWidget(scrollArea);
    layout->addLayout(buttonLayout);

    setLayout(layout);



    // Connect buttons to slots
    connect(applyFilterButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onApplyFilters);
    connect(nextPageButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onNextPage);
    connect(previousPageButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onPreviousPage);
}

// Load compliance thresholds
void ComplianceDashboardPage::loadComplianceThresholds(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open compliance thresholds file.");
        return;
    }

    QTextStream in(&file);
    complianceThresholds.clear();
    bool isFirstLine = true;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (isFirstLine) { isFirstLine = false; continue; } // Skip header

        QStringList fields = line.split(',');
        if (fields.size() == 2) {
            QString pollutant = fields[0].trimmed();
            double threshold = fields[1].toDouble();
            complianceThresholds[pollutant] = threshold;
        }
    }

    file.close();
    populateFilters();
}

// Populate filters dynamically
void ComplianceDashboardPage::populateFilters() {
    locationFilter->clear();
    pollutantFilter->clear();

    locationFilter->addItem("All Locations");
    pollutantFilter->addItem("All Pollutants");
    complianceStatusFilter->addItem("All Compliance");
    complianceStatusFilter->addItem("Compliant");
    complianceStatusFilter->addItem("Non-Compliant");
    complianceStatusFilter->addItem("Near Compliance");


    QSet<QString> locations;
    QSet<QString> pollutants;

    std::cout << "Populating filters...\n";

    for (const auto& record : model->getDataset().getData()) {
        QString location = QString::fromStdString(record.getSamplingPointLabel());
        QString pollutant = QString::fromStdString(record.getDeterminandLabel());
        
        location.toStdString();
        pollutant.toStdString();

        locations.insert(location);
        pollutants.insert(pollutant);
    }

    locationFilter->addItems(locations.values());
    pollutantFilter->addItems(pollutants.values());

}
// Apply filters and prepare data for pagination
void ComplianceDashboardPage::onApplyFilters() {
    filteredData.clear();

    QString selectedLocation = locationFilter->currentText();
    QString selectedPollutant = pollutantFilter->currentText();
    QString selectedComplianceStatus = complianceStatusFilter->currentText();

    for (const auto& record : model->getDataset().getData()) {
        QString location = QString::fromStdString(record.getSamplingPointLabel());
        QString pollutant = QString::fromStdString(record.getDeterminandLabel());
        double result = QString::fromStdString(record.getResult()).toDouble();

        if ((selectedLocation == "All Locations" || location == selectedLocation) &&
            (selectedPollutant == "All Pollutants" || pollutant == selectedPollutant)) {

            if (complianceThresholds.contains(pollutant)) {
                double threshold = complianceThresholds[pollutant];
                QString complianceStatus;

                if (result <= threshold * 0.95) {
                    complianceStatus = "Compliant";
                } else if (result <= threshold) {
                    complianceStatus = "Near Compliance";
                } else {
                    complianceStatus = "Non-Compliant";
                }

                if (selectedComplianceStatus == "All Compliance" || complianceStatus == selectedComplianceStatus) {
                    QMap<QString, QVariant> recordMap;
                    recordMap["location"] = location;
                    recordMap["pollutant"] = pollutant;
                    recordMap["result"] = result;
                    recordMap["status"] = complianceStatus;
                    filteredData.append(recordMap);
                }
            }
        }
    }

    currentPage = 0; // Reset to the first page
    updatePagination();
}
void ComplianceDashboardPage::updatePagination() {
    // Clear previous content in grid layout
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }

    const int cardsPerRow = 2; // Number of cards per row
    int startIndex = currentPage * itemsPerPage;
    int endIndex = qMin(startIndex + itemsPerPage, filteredData.size());

    int row = 0, col = 0; // Grid position tracking

    for (int i = startIndex; i < endIndex; ++i) {
        const auto& record = filteredData[i];

        // Create card
        QWidget* card = new QWidget(this);
        QVBoxLayout* cardLayout = new QVBoxLayout(card);

        QLabel* locationLabel = new QLabel(QString("Location: %1").arg(record["location"].toString()), this);
        QLabel* pollutantLabel = new QLabel(QString("Pollutant: %1").arg(record["pollutant"].toString()), this);
        QLabel* resultLabel = new QLabel(QString("Result: %1").arg(record["result"].toDouble()), this);
        QLabel* statusLabel = new QLabel(QString("Status: %1").arg(record["status"].toString()), this);

        // Set card background color
        QString color = record["status"] == "Compliant" ? "green" :
                        record["status"] == "Near Compliance" ? "orange" : "red";
        card->setStyleSheet(QString("background-color: %1; border-radius: 5px; padding: 10px;").arg(color));

        // Add labels to card
        cardLayout->addWidget(locationLabel);
        cardLayout->addWidget(pollutantLabel);
        cardLayout->addWidget(resultLabel);
        cardLayout->addWidget(statusLabel);
        cardLayout->setContentsMargins(5, 5, 5, 5);
        cardLayout->setSpacing(5);

        // Add card to the grid layout
        gridLayout->addWidget(card, row, col);

        // Update grid position
        if (++col == cardsPerRow) {
            col = 0;
            ++row;
        }
    }

    // Update pagination buttons
    previousPageButton->setEnabled(currentPage > 0);
    nextPageButton->setEnabled(endIndex < filteredData.size());
}

// Slot for next page
void ComplianceDashboardPage::onNextPage() {
    if ((currentPage + 1) * itemsPerPage < filteredData.size()) {
        ++currentPage;
        updatePagination();
    }
}

// Slot for previous page
void ComplianceDashboardPage::onPreviousPage() {
    if (currentPage > 0) {
        --currentPage;
        updatePagination();
    }
}
