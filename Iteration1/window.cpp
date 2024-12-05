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
    PollutantOverviewPage* pollutantOverviewPage = new PollutantOverviewPage();
    POPsPage* popsPage = new POPsPage();
    EnvironmentalLitterIndicatorsPage* litterPage = new EnvironmentalLitterIndicatorsPage();
    FluorinatedCompoundsPage* fluorinatedPage = new FluorinatedCompoundsPage();
    ComplianceDashboardPage* compliancePage = new ComplianceDashboardPage();
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


/*void QuakeWindow::createFileSelectors()
{
  QStringList significanceOptions;
  significanceOptions << "significant" << "4.5" << "2.5" << "1.0" << "all";
  significance = new QComboBox();
  significance->addItems(significanceOptions);

  QStringList periodOptions;
  periodOptions << "hour" << "day" << "week" << "month";
  period = new QComboBox();
  period->addItems(periodOptions);
}*/


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


void waterQualityWindow::createStatusBar() {
    fileInfo = new QLabel("Current file: <none>");
    QStatusBar* status = statusBar();
    status->addWidget(fileInfo);

    // Add the progress bar
    progressBar = new QProgressBar(this);
    progressBar->setRange(0, 100);
    progressBar->setValue(0);
    progressBar->setTextVisible(true);
    progressBar->setVisible(false); // Initially hidden
    status->addPermanentWidget(progressBar);
}



void waterQualityWindow::addFileMenu()
{
    QAction* setFileAction = new QAction("Select &File and Load", this);
    setFileAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_O));
    connect(setFileAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

    QAction* closeAction = new QAction("Quit", this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(setFileAction);
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


void waterQualityWindow::setDataLocation() {
    progressBar->setVisible(true);
    progressBar->setValue(0);

    QString filePath = QFileDialog::getOpenFileName(
        this, "Select CSV File", ".", "CSV Files (*.csv)"
    );

    if (filePath.isEmpty()) {
        QMessageBox::information(this, "No File Selected", "Please select a valid CSV file.");
        return;
    }

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName(); // Just the file name, no path

    try {
        model.updateFromFile(filePath); 
        qDebug() << "File loaded successfully!";
    } catch (const std::exception& error) {
        QMessageBox::critical(this, "CSV File Error",
            QString("Error loading file: %1\n\nError: %2")
            .arg(filePath)
            .arg(error.what()));
        progressBar->setVisible(false);
        return;
    }
    QTimer *timer = new QTimer(this);
    int progressValue = 0;
    connect(timer, &QTimer::timeout, [=, this]() mutable {
        progressValue += 11;
        progressBar->setValue(progressValue);

        if (progressValue == 99) {
            timer->stop();
            progressBar->setVisible(false);
            this->fileInfo->setText(QString("Current file: %1").arg(fileName));
            table->resizeColumnsToContents();
        }
    });

    timer->start(400); // Update progress bar every 100 milliseconds
}


/*
void waterQualityWindow::displayStats()
{
    if (model.hasData()) {
        if (statsDialog == nullptr) {
            statsDialog = new StatsDialog(this);
        }

        statsDialog->update(model.meanResult(), 
                          model.highestResult().getResult());

        statsDialog->show();
        statsDialog->raise();
        statsDialog->activateWindow();
    }
}
*/

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

