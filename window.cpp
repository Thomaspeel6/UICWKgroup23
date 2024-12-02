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
    table->setModel(&model);
    tabWidget = new QTabWidget();
    QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    table->setFont(tableFont);

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    
    PollutantOverviewPage* pollutantOverviewPage = new PollutantOverviewPage();
    POPsPage* popsPage = new POPsPage();
    EnvironmentalLitterIndicatorsPage* litterPage = new EnvironmentalLitterIndicatorsPage();
    FluorinatedCompoundsPage* fluorinatedPage = new FluorinatedCompoundsPage();
    ComplianceDashboardPage* compliancePage = new ComplianceDashboardPage();

    // Add tabs to the tab widget
    tabWidget->addTab(dashboardPage, "Dashboard");
    tabWidget->addTab(pollutantOverviewPage, "Pollutant Overview");
    tabWidget->addTab(popsPage, "POPs");
    tabWidget->addTab(litterPage, "Environmental Litter Indicators");
    tabWidget->addTab(fluorinatedPage, "Fluorinated Compounds");
    tabWidget->addTab(compliancePage, "Compliance Dashboard");

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
    loadButton = new QPushButton("Load Data");
    statsButton = new QPushButton("Statistics");

    connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
    connect(statsButton, SIGNAL(clicked()), this, SLOT(displayStats()));
}


void waterQualityWindow::createToolBar()
{
    QToolBar* toolBar = new QToolBar();

    toolBar->addWidget(loadButton);
    toolBar->addWidget(statsButton);

    addToolBar(Qt::TopToolBarArea, toolBar);
}


void waterQualityWindow::createStatusBar()
{
    fileInfo = new QLabel("Current file: <none>");
    QStatusBar* status = statusBar();
    status->addWidget(fileInfo);
}


void waterQualityWindow::addFileMenu()
{
    QAction* locAction = new QAction("Set Data &Location", this);
    locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
    connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

    QAction* closeAction = new QAction("Quit", this);
    closeAction->setShortcut(QKeySequence::Close);
    connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(locAction);
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


void waterQualityWindow::setDataLocation()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, "Data Location", ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (directory.length() > 0) {
        dataLocation = directory;
    }
}


void waterQualityWindow::openCSV()
{
    if (dataLocation.isEmpty()) {
        QMessageBox::critical(this, "Data Location Error",
            "Data location has not been set!\n\n"
            "You can specify this via the File menu."
        );
        return;
    }

    QString path = dataLocation + "/Y-2024.csv";

    try {
        model.updateFromFile(path);
    }
    catch (const std::exception& error) {
        QMessageBox::critical(this, "CSV File Error", 
            QString("Error loading file: %1\n\nError: %2")
            .arg(path)
            .arg(error.what()));
        return;
    }

    fileInfo->setText(QString("Current file: <kbd>Y-2024.csv</kbd>"));
    table->resizeColumnsToContents();

/*  if (statsDialog != nullptr && statsDialog->isVisible()) {
        statsDialog->update(model.meanResult(), 
                            model.highestResult().getResult());
    }*/

    if (statsDialog != nullptr && statsDialog->isVisible()) {
        statsDialog->update("N/A", "N/A");
    }
    qDebug() << "Trying to open file:" << path;
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
