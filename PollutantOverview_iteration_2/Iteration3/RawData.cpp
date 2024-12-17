#include "RawData.hpp"
#include "model.hpp"  // Include waterQualityModel definition here
#include <QVBoxLayout>

RawData::RawData(waterQualityModel* model, QWidget* parent)
    : QWidget(parent), tableView(new QTableView(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    tableView->setModel(model); // Connect the model to the table view

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);


    layout->addWidget(tableView);
    setLayout(layout);
}
