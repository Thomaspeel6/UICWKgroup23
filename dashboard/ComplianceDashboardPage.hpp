#ifndef COMPLIANCE_DASHBOARD_PAGE_HPP
#define COMPLIANCE_DASHBOARD_PAGE_HPP

#include <QWidget>
#include <QMainWindow>
#include <QPushButton>

class ComplianceDashboardPage : public QWidget
{
    Q_OBJECT

public:
    explicit ComplianceDashboardPage(QWidget* parent = nullptr);

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
