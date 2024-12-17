#include "ComplianceDashboardPage.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QScrollArea>



ComplianceDashboardPage::ComplianceDashboardPage(waterQualityModel* model, QWidget* parent)
    : QWidget(parent), model(model), currentPage(0)
{
    // UI components
    locationFilter = new QComboBox(this);
    pollutantFilter = new QComboBox(this);
    complianceStatusFilter = new QComboBox(this);
    applyFilterButton = new QPushButton("Apply Filters", this);
    
    // buttons layout 
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    previousPageButton = new QPushButton("Previous", this);
    nextPageButton = new QPushButton("Next", this);

    buttonLayout->addWidget(previousPageButton);
    buttonLayout->addWidget(nextPageButton);

    buttonLayout->setAlignment(Qt::AlignCenter);

    // card layouts
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    cardContainer = new QWidget();
    gridLayout = new QGridLayout(cardContainer);

    scrollArea->setWidget(cardContainer);

    // setting the main layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(locationFilter);
    layout->addWidget(pollutantFilter);
    layout->addWidget(complianceStatusFilter);
    layout->addWidget(applyFilterButton);
    layout->addWidget(scrollArea);
    layout->addLayout(buttonLayout);

    setLayout(layout);



    // connecting the buttons to slots
    connect(applyFilterButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onApplyFilters);
    connect(nextPageButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onNextPage);
    connect(previousPageButton, &QPushButton::clicked, this, &ComplianceDashboardPage::onPreviousPage);
}

// loaidng compliance thresholds
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

// populate the  filters dynamically
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
// apply filters and upadte for pagination
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

    currentPage = 0; 
    updatePagination();
}
void ComplianceDashboardPage::updatePagination() {
    // cleaver the  previous content in grid layout
    QLayoutItem* child;
    while ((child = gridLayout->takeAt(0)) != nullptr) {
        if (child->widget()) delete child->widget();
        delete child;
    }

    const int cardsPerRow = 2; 
    int startIndex = currentPage * itemsPerPage;
    int endIndex = qMin(startIndex + itemsPerPage, filteredData.size());

    int row = 0, col = 0;

    for (int i = startIndex; i < endIndex; ++i) {
        const auto& record = filteredData[i];

        // creating the card
        QWidget* card = new QWidget(this);
        QVBoxLayout* cardLayout = new QVBoxLayout(card);

        QLabel* locationLabel = new QLabel(QString("Location: %1").arg(record["location"].toString()), this);
        QLabel* pollutantLabel = new QLabel(QString("Pollutant: %1").arg(record["pollutant"].toString()), this);
        QLabel* resultLabel = new QLabel(QString("Result: %1").arg(record["result"].toDouble()), this);
        QLabel* statusLabel = new QLabel(QString("Status: %1").arg(record["status"].toString()), this);

        // setting card background color for ease of compliance undesrtanding
        QString color = record["status"] == "Compliant" ? "green" :
                        record["status"] == "Near Compliance" ? "orange" : "red";
        card->setStyleSheet(QString("background-color: %1; border-radius: 5px; padding: 10px;").arg(color));

 
        cardLayout->addWidget(locationLabel);
        cardLayout->addWidget(pollutantLabel);
        cardLayout->addWidget(resultLabel);
        cardLayout->addWidget(statusLabel);
        cardLayout->setContentsMargins(5, 5, 5, 5);
        cardLayout->setSpacing(5);


        gridLayout->addWidget(card, row, col);


        if (++col == cardsPerRow) {
            col = 0;
            ++row;
        }
    }

    previousPageButton->setEnabled(currentPage > 0);
    nextPageButton->setEnabled(endIndex < filteredData.size());
}


void ComplianceDashboardPage::onNextPage() {
    if ((currentPage + 1) * itemsPerPage < filteredData.size()) {
        ++currentPage;
        updatePagination();
    }
}


void ComplianceDashboardPage::onPreviousPage() {
    if (currentPage > 0) {
        --currentPage;
        updatePagination();
    }
}
