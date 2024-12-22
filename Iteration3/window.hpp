#pragma once

#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include "model.hpp"
#include "ComplianceDashboardPage.hpp"
#include "FluorinatedCompoundsPage.hpp"

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

private:
    void createMainWidget();
    void retranslateUi();

    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

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
    FluorinatedCompoundsPage* fluorinatedPage;
    QTableView* table;
    QLabel* fileInfoLabel;
    QLabel * complianceLabel;
    QTabWidget* tabWidget;
    StatsDialog* statsDialog;
    QProgressBar* progressBar;
    QTranslator translator;

    private slots:
        void uploadRealData();
    void uploadComplianceData();
    void startProgressBar(const QString& message);
    void updateProgressBar(QTimer* timer, const QString& successMessage);

    void onLanguageChanged();
    void about();
    signals:
        void languageChanged(); // change language signal
};
