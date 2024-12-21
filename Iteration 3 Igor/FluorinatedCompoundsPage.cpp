#include "FluorinatedCompoundsPage.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QSet>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QScrollArea>
#include <QToolTip>
#include <QDate>
#include <QtCharts/QCategoryAxis>

FluorinatedCompoundsPage::FluorinatedCompoundsPage(waterQualityModel* model, QWidget* parent)
    : QWidget(parent), model(model)
{
    // Page heading
    QLabel* pageHeading = new QLabel("Fluorinated Compounds", this);
    pageHeading->setAlignment(Qt::AlignCenter);
    pageHeading->setStyleSheet("font-size: 18px; font-weight: bold; margin-bottom: 10px;");

    // UI components
    fluorineLocationFilter = new QComboBox(this);
    fluorinePollutantFilter = new QComboBox(this);
    applyFluorineFilterButton = new QPushButton("Apply Filters", this);
    pollutantLevelLabel = new QLabel("Selected Pollutant Level: N/A", this);

    // Compliance indication label and box
    QLabel* complianceLabel = new QLabel("Compliance Indication:", this);
    complianceLabel->setToolTip("Compliance indicator:\n"
                                "Green: Safe levels below 0.075 µg/L\n"
                                "Orange: Moderate levels (0.075-0.1 µg/L)\n"
                                "Red: Unsafe levels above 0.1 µg/L\n\n"
                                "PFAS chemicals are persistent in the environment and linked to health risks like cancer and immune issues.");

    complianceIndicator = new QLabel(this);
    complianceIndicator->setFixedSize(20, 20); // Box size
    complianceIndicator->setStyleSheet("background-color: gray; border: 1px solid black;");
    complianceIndicator->setToolTip("Compliance indicator:\n"
                                    "Green: Safe levels below 0.075 µg/L\n"
                                    "Orange: Moderate levels (0.075-0.1 µg/L)\n"
                                    "Red: Unsafe levels above 0.1 µg/L\n\n"
                                    "PFAS chemicals are persistent in the environment and linked to health risks like cancer and immune issues.");

    QHBoxLayout* complianceLayout = new QHBoxLayout();
    complianceLayout->addWidget(complianceLabel);
    complianceLayout->addWidget(complianceIndicator);

    QVBoxLayout* pollutantLevelLayout = new QVBoxLayout();
    pollutantLevelLayout->addWidget(pollutantLevelLabel);
    pollutantLevelLayout->addLayout(complianceLayout); // Add the compliance layout under pollutant level

    // Card layouts
    fluorineScrollArea = new QScrollArea(this);
    fluorineScrollArea->setWidgetResizable(true);
    fluorineCardContainer = new QWidget();
    fluorineGridLayout = new QGridLayout(fluorineCardContainer);
    fluorineScrollArea->setWidget(fluorineCardContainer);

    // Setting the main layout
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(pageHeading);
    layout->addWidget(fluorineLocationFilter);
    layout->addWidget(fluorinePollutantFilter);
    layout->addWidget(applyFluorineFilterButton);
    layout->addLayout(pollutantLevelLayout);
    layout->addWidget(fluorineScrollArea);
    setLayout(layout);


    connect(applyFluorineFilterButton, &QPushButton::clicked, this, &FluorinatedCompoundsPage::onApplyFluorineFilters);
}

// Loading fluorinated thresholds
void FluorinatedCompoundsPage::loadFluorinatedThresholds(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open fluorinated thresholds file.");
        return;
    }

    QTextStream in(&file);
    fluorineThresholds.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() == 2) {
            QString pollutant = fields[0].trimmed();
            double threshold = fields[1].toDouble();
            fluorineThresholds[pollutant] = threshold;
        }
    }

    file.close();
    populateFluorineFilters();
}

void FluorinatedCompoundsPage::populateFluorineFilters() {
    fluorineLocationFilter->clear();
    fluorinePollutantFilter->clear();

    fluorineLocationFilter->addItem("All Locations");
    fluorinePollutantFilter->addItem("All Pollutants");

    QSet<QString> locations;
    QSet<QString> pollutants;

    // Iterate through the dataset and filter out the fluorinated compounds
    for (const auto& record : model->getDataset().getData()) {
        QString location = QString::fromStdString(record.getSamplingPointLabel());
        QString pollutant = QString::fromStdString(record.getDeterminandLabel());
        QString definition = QString::fromStdString(record.getDeterminandDefinition()).trimmed(); // Use definition

        if (definition.contains("fluoro", Qt::CaseInsensitive)) {
            pollutants.insert(pollutant);  // Add pollutant based on its definition
        }

        locations.insert(location);
    }

    // Convert QSet to QStringList and sort alphabetically
    QStringList sortedLocations = locations.values();
    sortedLocations.sort();  // Sort alphabetically

    // Add sorted locations to the location filter dropdown
    fluorineLocationFilter->addItems(sortedLocations);
    fluorinePollutantFilter->addItems(pollutants.values());
}

void FluorinatedCompoundsPage::onApplyFluorineFilters() {
    fluorineFilteredData.clear();

    QString selectedLocation = fluorineLocationFilter->currentText();
    QString selectedPollutant = fluorinePollutantFilter->currentText();

    double totalResult = 0.0;
    int count = 0;

    for (const auto& record : model->getDataset().getData()) {
        QString location = QString::fromStdString(record.getSamplingPointLabel());
        QString pollutant = QString::fromStdString(record.getDeterminandLabel());
        QString dateStr = QString::fromStdString(record.getSampleDateTime());
        double result = QString::fromStdString(record.getResult()).toDouble();

        // Parse the date with time included
        QDateTime dateTime = QDateTime::fromString(dateStr, "yyyy-MM-ddTHH:mm:ss");
        if (!dateTime.isValid()) {
            std::cout << "Invalid date format: " << dateStr.toStdString() << std::endl;
            continue; // Skip invalid records
        }

        QDate date = dateTime.date();

        // Apply filters: Check if the record matches the selected location and pollutant
        if ((selectedLocation == "All Locations" || location == selectedLocation) &&
            (selectedPollutant == "All Pollutants" || pollutant == selectedPollutant)) {
            fluorineFilteredData.append(QPointF(date.toJulianDay(), result));
            totalResult += result;
            count++;
        }
    }

    updateFluorineChart();

    // Compliance and average pollutant level logic
    if (count > 0) {
        double averageResult = totalResult / count;
        QString formattedResult = QString::number(averageResult, 'f', 3);

        if (averageResult >= 1.0) {
            complianceIndicator->setStyleSheet("background-color: red; border: 1px solid black;");
        } else if (averageResult > 0.075) {
            complianceIndicator->setStyleSheet("background-color: orange; border: 1px solid black;");
        } else {
            complianceIndicator->setStyleSheet("background-color: green; border: 1px solid black;");
        }

        pollutantLevelLabel->setText(QString("%1 pollutant level: %2 µg/L\n"
                                             "Number of entries: %3")
                                         .arg(selectedPollutant)
                                         .arg(formattedResult)
                                         .arg(count));
    } else {
        pollutantLevelLabel->setText("Selected Pollutant Level: Not Available");
        complianceIndicator->setStyleSheet("background-color: gray; border: 1px solid black;");
    }
}

void FluorinatedCompoundsPage::updateFluorineChart() {

    if (!fluorineChart) {
        fluorineChart = new QChart();
        fluorineChart->setTitle("Filtered Fluorinated Compounds Data");
        fluorineChart->setAnimationOptions(QChart::SeriesAnimations);

        fluorineChartView = new QChartView(fluorineChart);
        fluorineChartView->setRenderHint(QPainter::Antialiasing);
        fluorineGridLayout->addWidget(fluorineChartView, 0, 0);


        yAxis = new QValueAxis();
        yAxis->setTitleText("Pollutant Level (µg/L)");
        yAxis->setRange(0.0, 1.0);
        fluorineChart->addAxis(yAxis, Qt::AlignLeft);


        fluorineSeries = new QLineSeries();
        fluorineChart->addSeries(fluorineSeries);
        fluorineSeries->attachAxis(yAxis);
    }


    fluorineSeries->replace(fluorineFilteredData);


    if (xAxis) {
        fluorineChart->removeAxis(xAxis);
        delete xAxis;  // Prevent memory leaks
    }


    xAxis = new QCategoryAxis();
    xAxis->setTitleText("Date (Every 2 Months)");
    fluorineChart->addAxis(xAxis, Qt::AlignBottom);
    fluorineSeries->attachAxis(xAxis);


    QDate startDate(2024, 1, 1);
    QDate endDate(2024, 12, 31);
    for (QDate date = startDate; date <= endDate; date = date.addMonths(2)) {
        int julianDay = date.toJulianDay();
        QString label = date.toString("dd.MM.yyyy");
        xAxis->append(label, julianDay);
    }

    xAxis->setRange(startDate.toJulianDay(), endDate.toJulianDay());


    yAxis->setRange(0.0, 1.0);


    fluorineChart->legend()->hide();

    fluorineChart->setTitle("Filtered Fluorinated Compounds Data Over the Past Year");
}


void FluorinatedCompoundsPage::showTooltip(const QPointF& point, bool state) {
    if (state) {
        QToolTip::showText(
            QCursor::pos(),
            QString("X: %1\nY: %2").arg(point.x()).arg(point.y()),
            this
        );
    } else {
        QToolTip::hideText();
    }
}