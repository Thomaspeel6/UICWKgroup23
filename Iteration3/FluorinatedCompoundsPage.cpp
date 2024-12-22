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
#include <QtCharts>

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
    QLabel* complianceLabel = new QLabel("Average Compliance Indication:", this);
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

    // Iterate "fluoro" only
    for (const auto& record : model->getDataset().getData()) {
        QString definition = QString::fromStdString(record.getDeterminandDefinition()).trimmed();


        if (!definition.contains("fluoro", Qt::CaseInsensitive)) {
            continue;
        }

        QString location = QString::fromStdString(record.getSamplingPointLabel());
        QString pollutant = QString::fromStdString(record.getDeterminandLabel());
        QString dateStr = QString::fromStdString(record.getSampleDateTime());
        double result = QString::fromStdString(record.getResult()).toDouble();

        QDateTime dateTime = QDateTime::fromString(dateStr, "yyyy-MM-ddTHH:mm:ss");
        if (!dateTime.isValid()) {
            continue; // Skip invalid records
        }

        QDate date = dateTime.date();

        // Apply location and pollutant filters
        if ((selectedLocation == "All Locations" || location == selectedLocation) &&
            (selectedPollutant == "All Pollutants" || pollutant == selectedPollutant)) {
            fluorineFilteredData.append(QPointF(date.toJulianDay(), result));
            totalResult += result;
            count++;
        }
    }

    // Compliance and average pollutant level logic
    if (count > 0) {
        double averageResult = totalResult / count;
        QString formattedResult = QString::number(averageResult, 'f', 3);

        if (averageResult >= 0.1) {
            complianceIndicator->setStyleSheet("background-color: red; border: 1px solid black;");
        } else if (averageResult > 0.075 && averageResult <= 0.1) {
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

    updateFluorineChart();
}

void FluorinatedCompoundsPage::updateFluorineChart() {
    QString selectedPollutant = fluorinePollutantFilter->currentText();

    QString chartTitle;
    if (selectedPollutant == "All Pollutants" || selectedPollutant.isEmpty()) {
        chartTitle = "Filtered Fluorinated Compounds Data";
    } else {
        chartTitle = QString("Pollutant: %1").arg(selectedPollutant);
    }


    if (!fluorineChart) {
        fluorineChart = new QChart();
        fluorineChartView = new QChartView(fluorineChart);
        fluorineChartView->setRenderHint(QPainter::Antialiasing);
        fluorineGridLayout->addWidget(fluorineChartView, 0, 0);

        yAxis = new QValueAxis();
        yAxis->setTitleText("Pollutant Level (µg/L)");
        yAxis->setRange(0.0, 0.2); // Set range from 0 to 0.2
        yAxis->setTickCount(6);    // Divide into 5 intervals (0.04 each)
        yAxis->setLabelFormat("%.2f");
        fluorineChart->addAxis(yAxis, Qt::AlignLeft);

        fluorineSeries = new QLineSeries();
        fluorineChart->addSeries(fluorineSeries);
        fluorineSeries->attachAxis(yAxis);

        connect(fluorineSeries, &QLineSeries::hovered, this, &FluorinatedCompoundsPage::showTooltip);

        fluorineChart->legend()->hide();
    }


    fluorineChart->setTitle(chartTitle);
    fluorineSeries->replace(QVector<QPointF>());


    std::sort(fluorineFilteredData.begin(), fluorineFilteredData.end(), [](const QPointF& a, const QPointF& b) {
        return a.x() < b.x();
    });

    fluorineSeries->append(fluorineFilteredData);


    if (!fluorineFilteredData.isEmpty()) {
        int startJulianDay = static_cast<int>(fluorineFilteredData.first().x());
        int endJulianDay = static_cast<int>(fluorineFilteredData.last().x());

        QDate startDate = QDate::fromJulianDay(startJulianDay);
        QDate endDate = QDate::fromJulianDay(endJulianDay);

        // Recreate the X-axis
        if (xAxis) {
            fluorineChart->removeAxis(xAxis);
            delete xAxis;
        }

        xAxis = new QCategoryAxis();
        xAxis->setTitleText("Date Of Samples Taken (Hover for date) (dd.mm.yyyy)");
        xAxis->setLabelsVisible(false); // Hide the X-axis labels visually
        fluorineChart->addAxis(xAxis, Qt::AlignBottom);
        fluorineSeries->attachAxis(xAxis);

        for (QDate date = startDate; date <= endDate; date = date.addMonths(2)) {
            int julianDay = date.toJulianDay();
            QString label = date.toString("dd.MM.yyyy");
            xAxis->append(label, julianDay);
        }

        xAxis->setRange(startJulianDay, endJulianDay);
    }
}

void FluorinatedCompoundsPage::showTooltip(const QPointF& point, bool state) {
    if (state) {
        QDate date = QDate::fromJulianDay(static_cast<int>(point.x()));
        QString dateString = date.toString("dd MMM yyyy");


        double pollutantLevelValue = point.y();
        QString pollutantLevel = QString::number(pollutantLevelValue, 'f', 3);

        // Determine compliance status
        QString complianceStatus;
        QString tooltipColor;

        // Check compliance levels
        if (pollutantLevelValue >= 0.1) {
            complianceStatus = "Non-compliant (Unsafe levels)";
            tooltipColor = "background-color: red; color: white; border: 1px solid black;";
        } else if (pollutantLevelValue > 0.075 && pollutantLevelValue <= 0.1) {
            complianceStatus = "Moderate (Caution advised)";
            tooltipColor = "background-color: orange; color: black; border: 1px solid black;";
        } else {
            complianceStatus = "Within safety limits";
            tooltipColor = "background-color: green; color: white; border: 1px solid black;";
        }

        // Show tooltip with human-readable values and compliance information
        QToolTip::showText(
            QCursor::pos(),
            QString("<div style='%1'>"
                    "Date: %2<br>"
                    "Pollutant Level: %3 µg/L<br>"
                    "Compliance: %4"
                    "</div>")
                .arg(tooltipColor)
                .arg(dateString)
                .arg(pollutantLevel)
                .arg(complianceStatus),
            this
        );
    } else {
        QToolTip::hideText();
    }
}



void FluorinatedCompoundsPage::retranslateUi() {
    QLabel* pageHeading = findChild<QLabel*>("pageHeading");
    if (pageHeading) {
        pageHeading->setText(tr("Fluorinated Compounds"));
    }

    fluorineLocationFilter->setItemText(0, tr("All Locations"));
    fluorinePollutantFilter->setItemText(0, tr("All Pollutants"));
    applyFluorineFilterButton->setText(tr("Apply Filters"));

    QLabel* complianceLabel = findChild<QLabel*>("complianceLabel");
    if (complianceLabel) {
        complianceLabel->setText(tr("Average Compliance Indication:"));
        complianceLabel->setToolTip(tr("Compliance indicator:\n"
                                       "Green: Safe levels below 0.075 µg/L\n"
                                       "Orange: Moderate levels (0.075-0.1 µg/L)\n"
                                       "Red: Unsafe levels above 0.1 µg/L\n\n"
                                       "PFAS chemicals are persistent in the environment and linked to health risks like cancer and immune issues."));
    }


    complianceIndicator->setToolTip(tr("Compliance indicator:\n"
                                       "Green: Safe levels below 0.075 µg/L\n"
                                       "Orange: Moderate levels (0.075-0.1 µg/L)\n"
                                       "Red: Unsafe levels above 0.1 µg/L\n\n"
                                       "PFAS chemicals are persistent in the environment and linked to health risks like cancer and immune issues."));


    pollutantLevelLabel->setText(tr("Selected Pollutant Level: N/A"));


    if (fluorineChart) {
        QString selectedPollutant = fluorinePollutantFilter->currentText();
        QString chartTitle = (selectedPollutant == tr("All Pollutants") || selectedPollutant.isEmpty())
                                 ? tr("Filtered Fluorinated Compounds Data")
                                 : tr("Pollutant: %1").arg(selectedPollutant);
        fluorineChart->setTitle(chartTitle);
    }
}
