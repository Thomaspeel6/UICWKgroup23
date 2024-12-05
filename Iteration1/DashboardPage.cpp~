#include "DashboardPage.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

DashboardPage::DashboardPage(QWidget* parent)
    : QWidget(parent)
{
    setupDashboard();
}

void DashboardPage::setupDashboard() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

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
    connect(pollutantBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPollutantOverview);
    connect(popsBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPOPsPage);
    connect(litterBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPollutantOverview);
    connect(fluorinatedBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPOPsPage);
    connect(complianceBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPollutantOverview);
    connect(hotspotBtn &QPushButton::clicked, this, &DashboardPage::navigateToPOPsPage);

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

void DashboardPage::navigateToPollutantOverview() {
    tabWidget->setCurrentIndex(1); // Navigate to "Pollutant Overview" tab
}

void DashboardPage::navigateToPOPsPage() {
    tabWidget->setCurrentIndex(2); // Navigate to "POPs" tab
}

void DashboardPage::navigateToLitterIndicatorsPage() {
    tabWidget->setCurrentIndex(3); // Navigate to "Litter Indicators" tab
}

void DashboardPage::navigateToFluorinatedCompoundsPage() {
    tabWidget->setCurrentIndex(4); // Navigate to "Fluorinated Compounds" tab
}

void DashboardPage::navigateToCompliancePage() {
    tabWidget->setCurrentIndex(5); // Navigate to "Compliance" tab
}

void DashboardPage::navigateToHotspotsPage() {
    tabWidget->setCurrentIndex(6); // Navigate to "Geographical Hotspots" tab
}

