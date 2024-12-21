// COMP2811 Coursework 2 sample solution: dialog

#pragma once

#include <QDialog>
#include <string>

class QLineEdit;
class QPushButton;

class StatsDialog: public QDialog
{
  public:
    StatsDialog(QWidget*);
    //void update(double, double);
    void update(std::string, std::string);
  private:
    QLineEdit* meanResult;
    QLineEdit* highestResult;
    QPushButton* closeButton;
    void createWidgets();
    void arrangeWidgets();
};
