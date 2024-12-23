#include <QtWidgets>
#include <stdexcept>
#include <iostream>


#include "window.hpp"
#include "stats.hpp"
#include "PollutantOverviewPage.hpp"
#include "POPsPage.hpp"
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
    setWindowTitle(tr("Water Quality Tool"));
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
    pollutantOverviewPage = new PollutantOverviewPage(&model, this);
    POPsPage* popsPage = new POPsPage(tabWidget, this);
    fluorinatedPage = new FluorinatedCompoundsPage(&model, this);
    compliancePage = new ComplianceDashboardPage(&model, this);
    DashboardPage* dashboardPage = new DashboardPage(tabWidget, this);

    // Add tabs to the tab widget
    tabWidget->addTab(rawData, tr("Raw Data"));
    tabWidget->addTab(dashboardPage, tr("Dashboard"));
    tabWidget->addTab(pollutantOverviewPage, tr("Pollutant Overview"));
    tabWidget->addTab(popsPage, tr("POPs"));
    tabWidget->addTab(fluorinatedPage, tr("Fluorinated Compounds"));
    tabWidget->addTab(compliancePage, tr("Compliance Dashboard"));

    tabWidget->setCurrentIndex(1);

    setCentralWidget(tabWidget);
}


void waterQualityWindow::createStatusBar()
{
    // create the status bar
    QStatusBar* status = statusBar();

    // file info label
    fileInfoLabel = new QLabel(tr("Current File: <none>"), this);
    status->addWidget(fileInfoLabel);

    // compliace data uploaded label
    QLabel* complianceLabel = new QLabel(tr("Compliance Data Uploaded:"), this);
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
    QAction* uploadRealDataAction = new QAction(tr("Upload &Data"), this);
    uploadRealDataAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_D));
    connect(uploadRealDataAction, &QAction::triggered, this, &waterQualityWindow::uploadRealData);

    QAction* uploadComplianceDataAction = new QAction(tr("Upload &Compliance Data"), this);
    uploadComplianceDataAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_C));
    connect(uploadComplianceDataAction, &QAction::triggered, this, &waterQualityWindow::uploadComplianceData);

    QAction* closeAction = new QAction(tr("Quit"), this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, &QAction::triggered, this, &QWidget::close);

    QMenu* fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(uploadRealDataAction);
    fileMenu->addAction(uploadComplianceDataAction);
    fileMenu->addAction(closeAction);
}



void waterQualityWindow::addHelpMenu()
{
    QAction* aboutAction = new QAction(tr("&About"), this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAction = new QAction(tr("About &Qt"), this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
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
        this, tr("Select Real Data CSV File"), ".", tr("CSV Files (*.csv)")
    );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, tr("No File Selected"), tr("Please select a valid CSV file."));
        return;
    }

    try {

        startProgressBar(tr("Loading data..."));

        model.updateFromFile(filePath);

        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();

        fileInfoLabel->setText(QString(tr("Loaded File: %1")).arg(fileName));


        QTimer* timer = new QTimer(this);
        updateProgressBar(timer, tr("Data loaded successfully!"));


        table->resizeColumnsToContents();
    } catch (const std::exception& error) {
        QMessageBox::critical(this, tr("Error"), QString(tr("Failed to load real data: %1")).arg(error.what()));
        progressBar->setVisible(false);
    }
}

void waterQualityWindow::uploadComplianceData() {
    QString filePath = QFileDialog::getOpenFileName(
        this, tr("Select Compliance Data CSV File"), ".", tr("CSV Files (*.csv)")
    );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, tr("No File Selected"), tr("Please select a valid CSV file."));
        return;
    }

    try {
        startProgressBar(tr("Loading compliance data..."));
        compliancePage->loadComplianceThresholds(filePath);
        fluorinatedPage->loadFluorinatedThresholds(filePath);
        pollutantOverviewPage->loadComplianceThresholds(filePath);


        QTimer* timer = new QTimer(this);
        updateProgressBar(timer, tr("Compliance data loaded successfully!"));
        complianceCheckBox->setChecked(true);

    } catch (const std::exception& e) {
        QMessageBox::critical(this, tr("Error"), QString(tr("Failed to load compliance data: %1")).arg(e.what()));
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
    QMessageBox::about(this, tr("About Water Quality Tool"),
      tr("Water Quality Tool displays and analyzes Water Quality loaded from ") +
      tr("a CSV file."));
}

void waterQualityWindow::createButtons() {
    statsButton = new QPushButton("Statistics");

    connect(statsButton, SIGNAL(clicked()), this, SLOT(displayStats()));
}

void waterQualityWindow::createToolBar() {
    QToolBar* toolBar = new QToolBar();

    toolBar->addWidget(statsButton);

    addToolBar(Qt::TopToolBarArea, toolBar);
}
