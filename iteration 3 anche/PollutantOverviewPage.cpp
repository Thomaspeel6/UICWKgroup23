#include <QtWidgets>
#include "PollutantOverviewPage.hpp"

PollutantOverviewPage::PollutantOverviewPage(waterQualityModel* modelPtr, QWidget *parent)
    : QWidget(parent)
    , model(modelPtr)
    , tooltipFormat(tr("Purpose: %1\nMaterial Type: %2\nResult: %3 %4\nSample Point: %5\nLocation: (%6, %7)\nIs Compliance Sample: %8"))
{
    setupUI();
    connectSignals();
    retranslateUi();
}

void PollutantOverviewPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Search section
    QHBoxLayout* searchLayout = new QHBoxLayout();
    
    // search box
    QGroupBox* searchGroup = new QGroupBox(tr("Search Controls"));
    QVBoxLayout* searchGroupLayout = new QVBoxLayout();
    
    // Pollutant
    QLabel* pollutantLabel = new QLabel(tr("Select Pollutant:"));
    searchCombo = new QComboBox();
    searchCombo->setEditable(true);
    searchCombo->setPlaceholderText(tr("Search pollutants"));
    searchCombo->setMinimumWidth(300);
    searchCombo->addItems(getAllPollutants());
    searchCombo->setStyleSheet(
        "QComboBox {"
        "   padding: 8px;"
        "   border: 1px solid #ced4da;"
        "   border-radius: 4px;"
        "   font-size: 14px;"
        "   min-width: 200px;"
        "}"
    );
    
    // Sample Points List
    QLabel* samplePointLabel = new QLabel(tr("Select Sampling Points:"));
    samplePointList = new QListWidget();
    samplePointList->setSelectionMode(QAbstractItemView::MultiSelection);
    samplePointList->setMinimumHeight(150);
    samplePointList->setMaximumHeight(200);
    samplePointList->setStyleSheet(
        "QListWidget {"
        "   border: 1px solid #ced4da;"
        "   border-radius: 4px;"
        "   padding: 5px;"
        "   background-color: white;"
        "}"
        "QListWidget::item {"
        "   padding: 5px;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #f8f9fa;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #e9ecef;"
        "   color: black;"
        "}"
    );
    
    // Search Button
    searchButton = new QPushButton(tr("Generate Chart"));
    searchButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #28a745;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 4px;"
        "   padding: 8px 15px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #218838;"
        "}"
    );
    
    // allocate position to search group
    searchGroupLayout->addWidget(pollutantLabel);
    searchGroupLayout->addWidget(searchCombo);
    searchGroupLayout->addWidget(samplePointLabel);
    searchGroupLayout->addWidget(samplePointList);
    searchGroupLayout->addWidget(searchButton);
    searchGroup->setLayout(searchGroupLayout);
    
    // Add search group
    searchLayout->addWidget(searchGroup);
    searchLayout->addStretch();
    mainLayout->addLayout(searchLayout);

    // Chart view
    chartView = new QChartView();
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(400);
    mainLayout->addWidget(chartView);
    
    setupChart();
}

void PollutantOverviewPage::setupChart(const QString& pollutantName)
{
    QChart* chart = new QChart();
    
    if (!pollutantName.isEmpty()) {
        QStringList selectedSamplePoints;
        for (QListWidgetItem* item : samplePointList->selectedItems()) {
            selectedSamplePoints << item->text();
        }
        
        if (selectedSamplePoints.isEmpty()) {
            chart->setTitle(tr("Pollutant Levels Over Time"));
            chartView->setChart(chart);
            return;
        }

        dataCache.remove(pollutantName);
        
        dataCache[pollutantName] = processData(pollutantName, selectedSamplePoints);
        
        const auto& data = dataCache[pollutantName];

        if (!data.isEmpty()) {
            // record data ranges
            double minY = std::numeric_limits<double>::max();
            double maxY = std::numeric_limits<double>::min();
            QDateTime minTime = QDateTime::fromString(data.first().dateTime, Qt::ISODate);
            QDateTime maxTime = minTime;
            
            QHash<QString, QVector<ProcessedPollutantData>> grouped;
            
            // calculate ranges
            for (const auto& point : data) {
                if (selectedSamplePoints.contains(point.samplingPoint)) {
                    minY = std::min(minY, point.result);
                    maxY = std::max(maxY, point.result);
                    
                    QDateTime dateTime = QDateTime::fromString(point.dateTime, Qt::ISODate);
                    minTime = qMin(minTime, dateTime);
                    maxTime = qMax(maxTime, dateTime);
                    
                    grouped[point.samplingPoint].append(point);
                }
            }
            
            // Create series of sample points
            for (auto it = grouped.begin(); it != grouped.end(); ++it) {
                QLineSeries* lineSeries = new QLineSeries();
                QScatterSeries* scatterSeries = new QScatterSeries();
                
                lineSeries->setName(it.key());
                scatterSeries->setName(it.key());
                
                for (const auto& point : it.value()) {
                    QDateTime dateTime = QDateTime::fromString(point.dateTime, Qt::ISODate);
                    qreal x = dateTime.toMSecsSinceEpoch();
                    qreal y = point.result;
                    
                    lineSeries->append(x, y);
                    scatterSeries->append(x, y);
                    
                    QColor color = point.isCompliance ? 
                        (point.result > maxY * 0.7 ? QColor(255, 204, 0) : Qt::green) : 
                        Qt::red;
                    
                    lineSeries->setColor(color);
                    scatterSeries->setColor(color);
                }
                
                scatterSeries->setMarkerSize(15);
                connect(scatterSeries, &QScatterSeries::clicked, this,
                    [this, scatterSeries](const QPointF& point) {
                        handleChartPointClick(scatterSeries, point);
                    });
                
                chart->addSeries(lineSeries);
                chart->addSeries(scatterSeries);
            }
            
            // Setup axes
            QDateTimeAxis* axisX = new QDateTimeAxis();
            QValueAxis* axisY = new QValueAxis();
            
            double yPadding = (maxY - minY) * 0.1;
            axisY->setRange(minY - yPadding, maxY + yPadding);
            axisX->setRange(minTime.addDays(-1), maxTime.addDays(1));
            
            axisX->setFormat("yyyy-MM-dd");
            axisY->setLabelFormat("%.4f");
            
            axisX->setTitleText(tr("Time"));
            axisY->setTitleText(tr("Result"));
            
            chart->addAxis(axisX, Qt::AlignBottom);
            chart->addAxis(axisY, Qt::AlignLeft);
            
            for (QAbstractSeries* series : chart->series()) {
                series->attachAxis(axisX);
                series->attachAxis(axisY);
            }
            
            chart->setTitle(tr("Pollutant Levels Over Time: %1").arg(pollutantName));
        }
    } else {
        chart->setTitle(tr("Pollutant Levels Over Time"));
    }
    
    chart->legend()->show();
    chartView->setChart(chart);
}

void PollutantOverviewPage::connectSignals()
{
    // Update sample points
    connect(searchCombo, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &PollutantOverviewPage::updateSamplePoints);
    
    // Filte pollutant
    connect(searchCombo, &QComboBox::editTextChanged, this, [this](const QString& text) {
        if (text.isEmpty()) {
            searchCombo->clear();
            searchCombo->addItems(getAllPollutants());
            return;
        }
        
        QStringList filteredItems;
        for (const QString& pollutant : getAllPollutants()) {
            if (pollutant.contains(text, Qt::CaseInsensitive)) {
                filteredItems << pollutant;
            }
        }
        
        if (!filteredItems.isEmpty()) {
            QString currentText = searchCombo->currentText();
            searchCombo->blockSignals(true);
            searchCombo->clear();
            searchCombo->addItems(filteredItems);
            searchCombo->setEditText(currentText);
            searchCombo->blockSignals(false);
        }
    });
    
    // search button click
    connect(searchButton, &QPushButton::clicked, this, [this]() {
        QString pollutantName = searchCombo->currentText();
        if (!pollutantName.isEmpty()) {
            setupChart(pollutantName);
        }
    });
}

QStringList PollutantOverviewPage::getAllPollutants() const 
{
    QSet<QString> pollutants;
    const auto& dataset = model->getDataset();
    for (size_t i = 0; i < dataset.getSize(); ++i) {
        pollutants.insert(QString::fromStdString(dataset.getRow(i).getDeterminandLabel()));
    }
    return pollutants.values();
}

void PollutantOverviewPage::updateSamplePoints(const QString& pollutantName)
{
    samplePointList->clear();
    QStringList samplePoints = getSamplePoints(pollutantName);
    samplePointList->addItems(samplePoints);
    
    dataCache.clear();
}

QStringList PollutantOverviewPage::getSamplePoints(const QString& pollutantName) const
{
    QSet<QString> points;
    const auto& dataset = model->getDataset();
    for (size_t i = 0; i < dataset.getSize(); ++i) {
        const auto& row = dataset.getRow(i);
        if (QString::fromStdString(row.getDeterminandLabel()) == pollutantName) {
            points.insert(QString::fromStdString(row.getSamplingPointLabel()));
        }
    }
    return points.values();
}

QVector<ProcessedPollutantData> PollutantOverviewPage::processData(const QString& pollutantName, const QStringList& selectedSamplePoints)
{
    QVector<ProcessedPollutantData> data;
    const auto& dataset = model->getDataset();
    
    for (size_t i = 0; i < dataset.getSize(); ++i) {
        const auto& row = dataset.getRow(i);
        // get point
        QString currentSamplePoint = QString::fromStdString(row.getSamplingPointLabel());
        
        if (QString::fromStdString(row.getDeterminandLabel()) == pollutantName &&
            selectedSamplePoints.contains(currentSamplePoint)) {
            
            ProcessedPollutantData point{
                QString::fromStdString(row.getSampleDateTime()),
                std::stod(row.getResult()),
                currentSamplePoint,
                QString::fromStdString(row.getMaterialType()),
                QString::fromStdString(row.getPurpose()),
                std::stoi(row.getEasting()),
                std::stoi(row.getNorthing()),
                row.getIsComplianceSample() == "true",
                QString::fromStdString(row.getUnit())
            };
            data.append(point);
        }
    }
    
    std::sort(data.begin(), data.end(),
        [](const auto& a, const auto& b) { return a.dateTime < b.dateTime; });
    
    return data;
}

void PollutantOverviewPage::handleChartPointClick(QScatterSeries* series, const QPointF& point)
{
    QString pollutantName = searchCombo->currentText();
    if (!dataCache.contains(pollutantName)) return;
    
    const auto& data = dataCache[pollutantName];
    QDateTime clickTime = QDateTime::fromMSecsSinceEpoch(point.x());
    
    for (const auto& dataPoint : data) {
        if (dataPoint.samplingPoint == series->name() &&
            QDateTime::fromString(dataPoint.dateTime, Qt::ISODate).toMSecsSinceEpoch() == point.x()) {
            
            QString tooltip = tooltipFormat
                .arg(dataPoint.purpose)
                .arg(dataPoint.materialType)
                .arg(dataPoint.result)
                .arg(dataPoint.unit)
                .arg(dataPoint.samplingPoint)
                .arg(dataPoint.easting)
                .arg(dataPoint.northing)
                .arg(dataPoint.isCompliance ? tr("Yes") : tr("No"));
            
            QToolTip::showText(QCursor::pos(), tooltip, chartView, QRect(), 5000);
            break;
        }
    }
}

void PollutantOverviewPage::handleDataUpdate(const QModelIndex&, const QModelIndex&, const QList<int>&)
{
    dataCache.clear();
    updateLists();
    setupChart();
}

void PollutantOverviewPage::retranslateUi()
{
    // Update search box
    QList<QGroupBox*> groupBoxes = findChildren<QGroupBox*>();
    if (!groupBoxes.isEmpty()) {
        groupBoxes[0]->setTitle(tr("Search Controls"));
    }

    // Update labels
    QList<QLabel*> labels = findChildren<QLabel*>();
    for (QLabel* label : labels) {
        if (label->text().contains("Select Pollutant")) {
            label->setText(tr("Select Pollutant:"));
        } else if (label->text().contains("Select Sampling")) {
            label->setText(tr("Select Sampling Points:"));
        }
    }

    // Update combobox
    searchCombo->setPlaceholderText(tr("Search pollutants"));
    
    // Update button
    searchButton->setText(tr("Generate Chart"));

    // Update exist chart elements
    if (chartView && chartView->chart()) {
        QString currentTitle = chartView->chart()->title();
        if (currentTitle.contains(":")) {
            QString pollutantName = currentTitle.split(":").last().trimmed();
            chartView->chart()->setTitle(tr("Pollutant Levels Over Time: %1").arg(pollutantName));
        } else {
            chartView->chart()->setTitle(tr("Pollutant Levels Over Time"));
        }

        // axes titles
        for (QAbstractAxis* axis : chartView->chart()->axes()) {
            if (axis->orientation() == Qt::Horizontal) {
                axis->setTitleText(tr("Time"));
            } else if (axis->orientation() == Qt::Vertical) {
                axis->setTitleText(tr("Result"));
            }
        }
    }

    // Update tool tips
    tooltipFormat = tr("Purpose: %1\n"
                      "Material Type: %2\n"
                      "Result: %3 %4\n"
                      "Sample Point: %5\n"
                      "Location: (%6, %7)\n"
                      "Is Compliance Sample: %8");
}

void PollutantOverviewPage::updateLists()
{
    searchCombo->clear();
    searchCombo->addItems(getAllPollutants());
    samplePointList->clear();
    
    // Update sample points location
    QString currentPollutant = searchCombo->currentText();
    if (!currentPollutant.isEmpty()) {
        updateSamplePoints(currentPollutant);
    }
}