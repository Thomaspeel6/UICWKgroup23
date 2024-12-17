#pragma once

#include <QAbstractTableModel>
#include "dataset.hpp"

class waterQualityModel: public QAbstractTableModel
{
  public:
    waterQualityModel(QObject* parent = nullptr): QAbstractTableModel(parent) {}
    void updateFromFile(const QString&);
    bool hasData() const { return dataset.getSize() > 0; }
    const waterQualityDataset& getDataset() const { return dataset; }
    int rowCount(const QModelIndex& index) const { return dataset.getSize(); }
    int columnCount(const QModelIndex& index) const { return 17; }
    QVariant data(const QModelIndex&, int) const;
    QVariant headerData(int, Qt::Orientation, int) const;
    const std::vector<waterQuality>& getEntries() const;

/*  double meanResult() const { return dataset.meanResult(); }
    waterQuality highestResult() const { return dataset.highestResult(); }
    waterQuality lowestResult() const { return dataset.lowestResult(); }
*/ 
  private:
    waterQualityDataset dataset;
};
