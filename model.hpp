#pragma once

#include <QAbstractTableModel>
#include "dataset.hpp"

class waterQualityModel: public QAbstractTableModel
{
  public:
    waterQualityModel(QObject* parent = nullptr): QAbstractTableModel(parent) {}
    void updateFromFile(const QString&);
    bool hasData() const { return dataset.size() > 0; }

    int rowCount(const QModelIndex& index) const { return dataset.size(); }
    int columnCount(const QModelIndex& index) const { return 9; }
    QVariant data(const QModelIndex&, int) const;
    QVariant headerData(int, Qt::Orientation, int) const;

/*  double meanResult() const { return dataset.meanResult(); }
    waterQuality highestResult() const { return dataset.highestResult(); }
    waterQuality lowestResult() const { return dataset.lowestResult(); }
*/ 
  private:
    waterQualityDataset dataset;
};
