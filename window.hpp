#pragma once

#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include "model.hpp"
#include "ComplianceDashboardPage.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

class waterQualityWindow: public QMainWindow
{
    Q_OBJECT

public:
    waterQualityWindow();

    void changeLanguage(const QString& languageCode);


private slots:
    void uploadRealData();
    void uploadComplianceData();
    void startProgressBar(const QString& message);
    void updateProgressBar(QTimer* timer, const QString& successMessage);

    void displayStats();
    void onLanguageChanged();
    void about();
    
private:
    void createMainWidget();
    //void createFileSelectors();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();
    void retranslateUi();

    waterQualityModel model;
    QCheckBox* complianceCheckBox;
    QString dataLocation;
    QComboBox* pollutantType;
    QComboBox* location;
    QComboBox* timeRange;
    QPushButton* loadButton;
    QPushButton* statsButton;
    QPushButton* uploadComplianceDataButton;
    ComplianceDashboardPage* compliancePage;
    QTableView* table;
    QLabel* fileInfoLabel;
    QLabel * complianceLabel;
    QTabWidget* tabWidget;
    StatsDialog* statsDialog;
    QProgressBar* progressBar;
    QTranslator translator;


signals:
    void languageChanged(); // Add the languageChanged signal


};