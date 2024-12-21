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
      waterQuality wq = dataset.getRow(index.row());
        switch (index.column()) {
            case 0: return QString::fromStdString(wq.getId());
            case 1: return QString::fromStdString(wq.getSamplingPoint());
            case 2: return QString::fromStdString(wq.getSamplingPointNotation());
            case 3: return QString::fromStdString(wq.getSamplingPointLabel());
            case 4: return QString::fromStdString(wq.getSampleDateTime());
            case 5: return QString::fromStdString(wq.getDeterminandLabel());
            case 6: return QString::fromStdString(wq.getDeterminandDefinition());
            case 7: return QString::fromStdString(wq.getDeterminandNotation());
            case 8: return QString::fromStdString(wq.getResultQualifier());
            case 9: return QString::fromStdString(wq.getResult());
            case 10: return QString::fromStdString(wq.getResultInterpretation());
            case 11: return QString::fromStdString(wq.getDeterminandLabel());
            case 12: return QString::fromStdString(wq.getMaterialType());
            case 13: return QString::fromStdString(wq.getIsComplianceSample());
            case 14: return QString::fromStdString(wq.getPurpose());
            case 15: return QString::fromStdString(wq.getEasting());
            case 16: return QString::fromStdString(wq.getNorthing());
            default: return QVariant();
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
        case 0: return "ID";
        case 1: return "Sampling Point";
        case 2: return "Sampling Point Notation";
        case 3: return "Sampling Point Label";
        case 4: return "Sample Date Time";
        case 5: return "Determinand Label";
        case 6: return "Determinand Definition";
        case 7: return "Determinand Notation";
        case 8: return "Result Qualifier Notation";
        case 9: return "Result";
        case 10: return "Coded Result Interpretation";
        case 11: return "Determinand Unit Label";
        case 12: return "Sample Material Type Label";
        case 13: return "Is Compliance Sample";
        case 14: return "Sample Purpose Label";
        case 15: return "Easting";
        case 16: return "Northing";
        default: return QVariant();
    }
}

