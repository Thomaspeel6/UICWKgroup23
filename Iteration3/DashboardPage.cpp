#include "DashboardPage.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QMenu>
#include <iostream>


DashboardPage::DashboardPage(QTabWidget* tabWidget, QWidget* parent)
    : QWidget(parent), tabWidget(tabWidget)
{
    setupDashboard();
}

void DashboardPage::setupDashboard() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    titleLabel = new QLabel(tr("Water Quality Monitor"), this);
    titleLabel->setAlignment(Qt::AlignCenter);
    QString style = "margin-top: 0%; font: bold 16px; text-align: center;";
    titleLabel->setStyleSheet(style);
    mainLayout->addWidget(titleLabel);

    QGridLayout *gridLayout = new QGridLayout();

    pollutantBtn = setCard(tr("Pollutant Overview"), "red");
    popsBtn = setCard(tr("POPs"), "orange");
    litterBtn = setCard(tr("Litter Indicators"), "green");
    fluorinatedBtn = setCard(tr("Fluorinated Compounds"), "orange");
    complianceBtn = setCard(tr("Compliance"), "green");
    hotspotBtn = setCard(tr("Geographical Hotspots"), "green");

    gridLayout->addWidget(pollutantBtn, 0, 0);
    gridLayout->addWidget(popsBtn, 0, 1);
    gridLayout->addWidget(litterBtn, 0, 2);
    gridLayout->addWidget(fluorinatedBtn, 1, 0);
    gridLayout->addWidget(complianceBtn, 1, 1);
    gridLayout->addWidget(hotspotBtn, 1, 2);

    mainLayout->addLayout(gridLayout);

    connect(pollutantBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPollutantOverview);
    connect(popsBtn, &QPushButton::clicked, this, &DashboardPage::navigateToPOPsPage);
    connect(litterBtn, &QPushButton::clicked, this, &DashboardPage::navigateToLitterIndicatorsPage);
    connect(fluorinatedBtn, &QPushButton::clicked, this, &DashboardPage::navigateToFluorinatedCompoundsPage);
    connect(complianceBtn, &QPushButton::clicked, this, &DashboardPage::navigateToCompliancePage);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    linksBtn = new QPushButton(tr("Links"), this);
    languageBtn = new QPushButton(tr("Language"), this);

    linksBtn->setMinimumSize(60, 30);
    linksBtn->setMaximumSize(120, 40);
    languageBtn->setMinimumSize(60, 30);
    languageBtn->setMaximumSize(120, 40);

    bottomLayout->addWidget(linksBtn);
    bottomLayout->addStretch();
    bottomLayout->addWidget(languageBtn);

    mainLayout->addLayout(bottomLayout);

    connect(languageBtn, &QPushButton::clicked, this, &DashboardPage::showLanguageMenu);


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

void DashboardPage::showLanguageMenu() {
    languageMenu = new QMenu(languageBtn);

    languageMenu->addAction(tr("English"), [=]() { emit requestLanguageChange("en"); });
    languageMenu->addAction(tr("French"), [=]() { emit requestLanguageChange("fr"); });
    languageMenu->addAction(tr("German"), [=]() { emit requestLanguageChange("de"); });

    languageMenu->exec(languageBtn->mapToGlobal(QPoint(0, languageBtn->height())));
}



void DashboardPage::navigateToPollutantOverview() {
    tabWidget->setCurrentIndex(2); // Navigate to "Pollutant Overview" tab
}

void DashboardPage::navigateToPOPsPage() {
    tabWidget->setCurrentIndex(3); // Navigate to "POPs" tab
}

void DashboardPage::navigateToLitterIndicatorsPage() {
    tabWidget->setCurrentIndex(4); // Navigate to "Litter Indicators" tab
}

void DashboardPage::navigateToFluorinatedCompoundsPage() {
    tabWidget->setCurrentIndex(5); // Navigate to "Fluorinated Compounds" tab
}

void DashboardPage::navigateToCompliancePage() {
    tabWidget->setCurrentIndex(6); // Navigate to "Compliance" tab
}

void DashboardPage::navigateToHotspotsPage() {
    tabWidget->setCurrentIndex(7); // Navigate to "Geographical Hotspots" tab
}

void DashboardPage::retranslateUi() {
    std::cout << "DashboardPage::retranslateUi() called" << std::endl;

    // Update the title label
    titleLabel->setText(tr("Water Quality Monitor"));

    // Update buttons on the grid
    pollutantBtn->setText(tr("Pollutant Overview"));
    popsBtn->setText(tr("POPs"));
    litterBtn->setText(tr("Litter Indicators"));
    fluorinatedBtn->setText(tr("Fluorinated Compounds"));
    complianceBtn->setText(tr("Compliance"));
    hotspotBtn->setText(tr("Geographical Hotspots"));

    // Update bottom buttons
    linksBtn->setText(tr("Links"));
    languageBtn->setText(tr("Language"));

    // Clear and rebuild the language menu (if needed)
    if (languageMenu) {
        languageMenu->clear();
        languageMenu->addAction(tr("English"), [=]() { emit requestLanguageChange("en"); });
        languageMenu->addAction(tr("French"), [=]() { emit requestLanguageChange("fr"); });
        languageMenu->addAction(tr("German"), [=]() { emit requestLanguageChange("de"); });
    }
}

