#ifndef DASHBOARD_PAGE_HPP
#define DASHBOARD_PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QTranslator>

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QTabWidget* tabWidget, QWidget* parent = nullptr);

private:
    QPushButton* setCard(const QString& text, const QString& color);
    void setupDashboard();

    QPushButton *pollutantBtn;
    QPushButton *popsBtn;
    QPushButton *litterBtn;
    QPushButton *fluorinatedBtn;
    QPushButton *complianceBtn;
    QPushButton *hotspotBtn;
    QPushButton *linksBtn;
    QPushButton *languageBtn;
    QTabWidget* tabWidget;

    QMenu *languageMenu;
    QTranslator translator;

private slots:
    void navigateToPollutantOverview();
    void navigateToPOPsPage();
    void navigateToLitterIndicatorsPage();
    void navigateToFluorinatedCompoundsPage();
    void navigateToCompliancePage();
    void navigateToHotspotsPage();

    void showLanguageMenu();
    void changeLanguage(const QString &languageCode);
};

#endif