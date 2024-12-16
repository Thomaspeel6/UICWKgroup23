#pragma once

#include <QMainWindow>
#include <QProgressBar>
#include <QTimer>
#include "model.hpp"

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
    QString dataLocation;
    QComboBox* pollutantType;
    QComboBox* location;
    QComboBox* timeRange;
    QPushButton* loadButton;
    QPushButton* statsButton;
    QTableView* table;
    QLabel* fileInfo;
    QTabWidget* tabWidget;
    StatsDialog* statsDialog;
    QProgressBar* progressBar;

private slots:
    void setDataLocation();
    void displayStats();
    void about();
};