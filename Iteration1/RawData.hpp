#pragma once 
#include <QWidget>
#include <QTableView>
#include <QHeaderView>  // Include this for QHeaderView
#include "model.hpp"  // Assuming this defines waterQualityModel

class RawData : public QWidget {
    Q_OBJECT

public:
    explicit RawData(waterQualityModel* model, QWidget* parent = nullptr);

private:
    QTableView* tableView;
};

