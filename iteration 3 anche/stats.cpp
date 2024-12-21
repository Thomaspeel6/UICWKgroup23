#include <QtWidgets>
#include "stats.hpp"


StatsDialog::StatsDialog(QWidget* parent): QDialog(parent)
{
  createWidgets();
  arrangeWidgets();
  setWindowTitle("Water Quality Stats");
}


/*
void StatsDialog::update(double mean, double highest)
{ 
  meanResult->setText(QString::number(mean, 'f', 1));
  highestResult->setText(QString::number(highest, 'f', 1));
}
*/


void StatsDialog::update(std::string mean, std::string highest)
{ 
    meanResult->setText(QString::fromStdString(mean));
    highestResult->setText(QString::fromStdString(highest));
}


void StatsDialog::createWidgets()
{
  meanResult = new QLineEdit("?");
  meanResult->setMaxLength(10);
  meanResult->setReadOnly(true);

  highestResult = new QLineEdit("?");
  highestResult->setMaxLength(10);
  highestResult->setReadOnly(true);

  closeButton = new QPushButton("Close");
  connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
}


void StatsDialog::arrangeWidgets()
{
  QFormLayout* form = new QFormLayout();
  form->addRow("Mean Result:", meanResult);
  form->addRow("Highest Result:", highestResult);

  QVBoxLayout* box = new QVBoxLayout();
  box->addLayout(form);
  box->addWidget(closeButton);

  setLayout(box);
}
