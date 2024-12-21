#ifndef DASHBOARD_PAGE_HPP
#define DASHBOARD_PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

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
    QPushButton *fluorinatedBtn;
    QPushButton *complianceBtn;
    QPushButton *linksBtn;
    QPushButton *languageBtn;
    QTabWidget* tabWidget;

    private slots:
        void navigateToPollutantOverview();
    void navigateToPOPsPage();
    void navigateToFluorinatedCompoundsPage();
    void navigateToCompliancePage();

};

#endif
