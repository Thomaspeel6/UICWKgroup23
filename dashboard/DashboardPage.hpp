#ifndef DASHBOARD_PAGE_HPP
#define DASHBOARD_PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

class DashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardPage(QWidget* parent = nullptr);

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

};

#endif 
