#include "model.hpp"


void waterQualityModel::updateFromFile(const QString& filename)
{
  beginResetModel();
  dataset.loadData(filename.toStdString());
  endResetModel();
}

QVariant waterQualityModel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }


    if (role == Qt::TextAlignmentRole) {
        switch (index.column()) {
            case 5:
                return int(Qt::AlignRight | Qt::AlignVCenter);
            default:
                return int(Qt::AlignLeft | Qt::AlignVCenter);
        }
    }
    else if (role == Qt::DisplayRole) {
        waterQuality wq = dataset[index.row()];
        switch (index.column()) {
            case 0: return QString::fromStdString(wq.getSamplingPointLabel());
            case 1: return QString::fromStdString(wq.getSampleDateTime());
            case 2: return QString::fromStdString(wq.getDeterminandLabel());
            case 3: return QString::fromStdString(wq.getDeterminandDefinition());
            case 4: return QString::fromStdString(wq.getResultQualifier());
//          case 5: return QVariant(wq.getResult());
            case 5: return QString::fromStdString(wq.getResult());
            case 6: return QString::fromStdString(wq.getUnit());
//          case 7: return QVariant(wq.getEasting());
//          case 8: return QVariant(wq.getNorthing());
            case 7: return QString::fromStdString(wq.getEasting());
            case 8: return QString::fromStdString(wq.getNorthing());
        }
    }

    return QVariant();
}


QVariant waterQualityModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Vertical) {
        return QVariant(section + 1);
    }

    switch (section) {
        case 0: return QString("Location");
        case 1: return QString("Date Time");
        case 2: return QString("Pollutant");
        case 3: return QString("Description");
        case 4: return QString("Qualifier");
        case 5: return QString("Result");
        case 6: return QString("Unit");
        case 7: return QString("Easting");
        case 8: return QString("Northing");
        default: return QVariant();
    }
}