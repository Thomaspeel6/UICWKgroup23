#ifndef DASHBOARD_PAGE_HPP
#define DASHBOARD_PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QMenu>
#include <QTranslator>
#include <QTabWidget>
#include <QLabel>

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QTabWidget* tabWidget, QWidget* parent = nullptr);


    public slots:
        void retranslateUi();

private:
    QPushButton* setCard(const QString& text, const QString& color);
    void setupDashboard();

    QLabel* titleLabel;
    QPushButton *pollutantBtn;
    QPushButton *popsBtn;
    QPushButton *fluorinatedBtn;
    QPushButton *complianceBtn;
    QPushButton *languageBtn;
    QTabWidget* tabWidget;

    QMenu *languageMenu;
    QTranslator translator;

    private slots:

        void navigateToPollutantOverview();
    void navigateToPOPsPage();
    void navigateToFluorinatedCompoundsPage();
    void navigateToCompliancePage();

    void showLanguageMenu();

    signals:
        void requestLanguageChange(const QString& languageCode);

};

#endif // DASHBOARD_PAGE_HPP
