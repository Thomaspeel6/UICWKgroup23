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

private:
    void createMainWidget();
    //void createFileSelectors();
    void createButtons();
    void createToolBar();
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
    QTableView* table;
    QLabel* fileInfoLabel;
    QTabWidget* tabWidget;
    StatsDialog* statsDialog;
    QProgressBar* progressBar;

private slots:
    void uploadRealData();
    void uploadComplianceData();
    void startProgressBar(const QString& message);
    void updateProgressBar(QTimer* timer, const QString& successMessage);

    void displayStats();
    void about();
};