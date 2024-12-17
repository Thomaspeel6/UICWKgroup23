#include <QtWidgets>
#include <stdexcept>
#include <iostream>


#include "window.hpp"
#include "stats.hpp"
#include "PollutantOverviewPage.hpp"
#include "POPsPage.hpp"
#include "EnvironmentalLitterIndicatorsPage.hpp"
#include "FluorinatedCompoundsPage.hpp"
#include "ComplianceDashboardPage.hpp"
#include "DashboardPage.hpp"
#include "RawData.hpp"

#include <QDebug>

static const int MIN_WIDTH = 1000;


waterQualityWindow::waterQualityWindow(): QMainWindow(), statsDialog(nullptr)
{
    createMainWidget();
    //createFileSelectors();
    createButtons();
    createToolBar();
    createStatusBar();
    addFileMenu();
    addHelpMenu();

    setMinimumWidth(MIN_WIDTH);
    setWindowTitle("Water Quality Tool");
}


void waterQualityWindow::createMainWidget()
{
    table = new QTableView();
    tabWidget = new QTabWidget(this);
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    RawData* rawData = new RawData(&model, this);
    PollutantOverviewPage* pollutantOverviewPage = new PollutantOverviewPage(this);
    POPsPage* popsPage = new POPsPage(tabWidget, this);
    EnvironmentalLitterIndicatorsPage* litterPage = new EnvironmentalLitterIndicatorsPage();
    FluorinatedCompoundsPage* fluorinatedPage = new FluorinatedCompoundsPage(this);
    compliancePage = new ComplianceDashboardPage(&model, this);
    DashboardPage* dashboardPage = new DashboardPage(tabWidget, this);

    // Add tabs to the tab widget
    tabWidget->addTab(rawData, "Raw Data");
    tabWidget->addTab(dashboardPage, "Dashboard");
    tabWidget->addTab(pollutantOverviewPage, "Pollutant Overview");
    tabWidget->addTab(popsPage, "POPs");
    tabWidget->addTab(litterPage, "Environmental Litter Indicators");
    tabWidget->addTab(fluorinatedPage, "Fluorinated Compounds");
    tabWidget->addTab(compliancePage, "Compliance Dashboard");

    tabWidget->setCurrentIndex(1);

    setCentralWidget(tabWidget);
}



void waterQualityWindow::createButtons()
{

    statsButton = new QPushButton("Statistics");

    connect(statsButton, SIGNAL(clicked()), this, SLOT(displayStats()));
}


void waterQualityWindow::createToolBar()
{
    QToolBar* toolBar = new QToolBar();

    toolBar->addWidget(statsButton);

    addToolBar(Qt::TopToolBarArea, toolBar);
}


void waterQualityWindow::createStatusBar()
{
    // create the status bar
    QStatusBar* status = statusBar();

    // file info label
    fileInfoLabel = new QLabel("Current File: <none>", this);
    status->addWidget(fileInfoLabel);

    // compliace data uploaded label
    QLabel* complianceLabel = new QLabel("Compliance Data Uploaded:", this);
    status->addWidget(complianceLabel);

    // compliance data checkbox
    complianceCheckBox = new QCheckBox(this);
    complianceCheckBox->setEnabled(false); 
    complianceCheckBox->setChecked(false); 
    status->addWidget(complianceCheckBox);

    // progress bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setVisible(false); // hidden unless called
    status->addPermanentWidget(progressBar);
}


void waterQualityWindow::addFileMenu()
{
    QAction* uploadRealDataAction = new QAction("Upload &Data", this);
    uploadRealDataAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));
    connect(uploadRealDataAction, &QAction::triggered, this, &waterQualityWindow::uploadRealData);

    QAction* uploadComplianceDataAction = new QAction("Upload &Compliance Data", this);
    uploadComplianceDataAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    connect(uploadComplianceDataAction, &QAction::triggered, this, &waterQualityWindow::uploadComplianceData);

    QAction* closeAction = new QAction("Quit", this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &QWidget::close);

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(uploadRealDataAction);
    fileMenu->addAction(uploadComplianceDataAction);
    fileMenu->addAction(closeAction);
}



void waterQualityWindow::addHelpMenu()
{
    QAction* aboutAction = new QAction("&About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAction = new QAction("About &Qt", this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void waterQualityWindow::startProgressBar(const QString& message)
{
    progressBar->setVisible(true);
    progressBar->setValue(0);
    statusBar()->showMessage(message);
}

void waterQualityWindow::updateProgressBar(QTimer* timer, const QString& successMessage)
{
    int progressValue = 0;

    connect(timer, &QTimer::timeout, [=, this]() mutable {
        progressValue += 11;
        progressBar->setValue(progressValue);

        if (progressValue >= 99) {
            timer->stop();
            progressBar->setVisible(false);
            statusBar()->showMessage(successMessage, 5000); 
        }
    });

    timer->start(400); 
}

void waterQualityWindow::uploadRealData()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Select Real Data CSV File", ".", "CSV Files (*.csv)"
    );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, "No File Selected", "Please select a valid CSV file.");
        return;
    }

    try {
        
        startProgressBar("Loading data...");

 
        model.updateFromFile(filePath);

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();

        fileInfoLabel->setText(QString("Loaded File: %1").arg(fileName));

    
        QTimer* timer = new QTimer(this);
        updateProgressBar(timer, "Data loaded successfully!");


        table->resizeColumnsToContents();
    } catch (const std::exception& error) {
        QMessageBox::critical(this, "Error", QString("Failed to load real data: %1").arg(error.what()));
        progressBar->setVisible(false);
    }
}

void waterQualityWindow::uploadComplianceData() {
    QString filePath = QFileDialog::getOpenFileName(
        this, "Select Compliance Data CSV File", ".", "CSV Files (*.csv)"
    );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, "No File Selected", "Please select a valid CSV file.");
        return;
    }

    try {
        startProgressBar("Loading compliance data...");
        compliancePage->loadComplianceThresholds(filePath);



        QTimer* timer = new QTimer(this);
        updateProgressBar(timer, "Compliance data loaded successfully!");
        complianceCheckBox->setChecked(true);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString("Failed to load compliance data: %1").arg(e.what()));
        progressBar->setVisible(false);
    }
}


void waterQualityWindow::displayStats()
{
    if (model.hasData()) {
        if (statsDialog == nullptr) {
            statsDialog = new StatsDialog(this);
        }

        statsDialog->update("N/A", "N/A"); // Changed from numerical values

        statsDialog->show();
        statsDialog->raise();
        statsDialog->activateWindow();
    }
}

void waterQualityWindow::about()
{
  QMessageBox::about(this, "About Water Quality Tool",
    "Water Quality Tool displays and analyzes Water Quality loaded from"
    "a CSV file");
}

