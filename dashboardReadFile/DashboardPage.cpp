#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "DashboardPage.hpp"
#include "stats.hpp"

#include <QDebug>

static const int MIN_WIDTH = 1000;


DashboardPage::DashboardPage(): QMainWindow(), statsDialog(nullptr)
{
    setupDashboard();
    createButtons();
    createToolBar();
    createStatusBar();
    addFileMenu();
    addHelpMenu();

    setMinimumSize(MIN_WIDTH, MIN_WIDTH);
    setWindowTitle("Water Quality Tool");
}


void DashboardPage::setupDashboard()
{
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QLabel *titleLabel = new QLabel("Water Quality Monitor", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QString style = "margin-top: 0%; font: bold 16px; text-align: center;";
    titleLabel->setStyleSheet(style);
    mainLayout->addWidget(titleLabel);

    QGridLayout *gridLayout = new QGridLayout();
    
    pollutantBtn = setCard("Pollutant overview", "red");
    popsBtn = setCard("POPs", "orange");
    litterBtn = setCard("Litter Indicators", "green");
    fluorinatedBtn = setCard("Fluorinated Compounds", "orange");
    complianceBtn = setCard("Compliance", "green");
    hotspotBtn = setCard("Geographical Hotspots", "green");

    gridLayout->addWidget(pollutantBtn, 0, 0);
    gridLayout->addWidget(popsBtn, 0, 1);
    gridLayout->addWidget(litterBtn, 0, 2);
    gridLayout->addWidget(fluorinatedBtn, 1, 0);
    gridLayout->addWidget(complianceBtn, 1, 1);
    gridLayout->addWidget(hotspotBtn, 1, 2);

    mainLayout->addLayout(gridLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    linksBtn = new QPushButton("Links", this);
    languageBtn = new QPushButton("Language", this);
    
    linksBtn->setMinimumSize(60, 30);
    linksBtn->setMaximumSize(120, 40);
    languageBtn->setMinimumSize(60, 30);
    languageBtn->setMaximumSize(120, 40);

    bottomLayout->addWidget(linksBtn);
    bottomLayout->addStretch();
    bottomLayout->addWidget(languageBtn);
    
    mainLayout->addLayout(bottomLayout);
}

QPushButton* DashboardPage::setCard(const QString& text, const QString& color) {
    QPushButton *button = new QPushButton(text, this);
    button->setMinimumSize(100, 50);
    button->setMaximumSize(400, 300);
    
    QString style;
    if (color == "red") {
        style = "background-color: #ff4444; color: white; border-radius: 5px; font: bold 14px;";}
    if (color == "orange") {
        style = "background-color: #ffbb33; color: black; border-radius: 5px; font: bold 14px;";}
    if (color == "green") {
        style = "background-color: #00C851; color: white; border-radius: 5px; font: bold 14px;";}
    button->setStyleSheet(style);
    
    return button;
}

void DashboardPage::createButtons()
{
    loadButton = new QPushButton("Load Data");

    connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}


void DashboardPage::createToolBar()
{
    QToolBar* toolBar = new QToolBar();

    toolBar->addWidget(loadButton);

    addToolBar(Qt::TopToolBarArea, toolBar);
}


void DashboardPage::createStatusBar()
{
    fileInfo = new QLabel("Current file: <none>");
    QStatusBar* status = statusBar();
    status->addWidget(fileInfo);
}


void DashboardPage::addFileMenu()
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


void DashboardPage::addHelpMenu()
{
    QAction* aboutAction = new QAction("&About", this);
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

    QAction* aboutQtAction = new QAction("About &Qt", this);
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}


void DashboardPage::setDataLocation()
{
    QString directory = QFileDialog::getExistingDirectory(
        this, "Data Location", ".",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if (directory.length() > 0) {
        dataLocation = directory;
    }
}


void DashboardPage::openCSV()
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

    if (statsDialog != nullptr && statsDialog->isVisible()) {
        statsDialog->update("N/A", "N/A");
    }
    qDebug() << "Trying to open file:" << path;
}

void DashboardPage::about()
{
  QMessageBox::about(this, "About Water Quality Tool",
    "Water Quality Tool displays and analyzes Water Quality loaded from"
    "a CSV file");
}
