#pragma once

#include <QMainWindow>
#include "model.hpp"
#include "PollutantOverviewPage.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class StatsDialog;

class DashboardPage: public QMainWindow
{
    Q_OBJECT

public:
    DashboardPage();

private:
    void setupDashboard();
    void setupMainDashboard();
    QPushButton* setCard(const QString& text, const QString& color);
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    // Data members
    waterQualityModel model;
    QString dataLocation;
    
    // Comboboxes
    QComboBox* pollutantType;
    QComboBox* location;
    QComboBox* timeRange;
    
    // Dashboard buttons
    QPushButton* pollutantBtn;
    QPushButton* popsBtn;
    QPushButton* litterBtn;
    QPushButton* fluorinatedBtn;
    QPushButton* complianceBtn;
    QPushButton* hotspotBtn;
    QPushButton* linksBtn;
    QPushButton* languageBtn;
    
    // Other UI elements
    QPushButton* loadButton;
    QLabel* fileInfo;
    StatsDialog* statsDialog;

    // change page
    PollutantOverviewPage* pollutantPage;

private slots:
    void setDataLocation();
    void openCSV();
    void about();
    void showPollutantPage();
};