#pragma once

#include <QString>
#include <vector>
#include <utility>
#include <QStringList>
#include "dataset.hpp"

class waterQualityModel 
{
public:
    waterQualityModel() {}
    void updateFromFile(const QString& filename)
    {
        dataset.loadData(filename.toStdString());
    }
    bool hasData() const { return dataset.size() > 0; }

    QStringList getAllPollutants() const {
        QStringList pollutants;
        for (int i = 0; i < dataset.size(); ++i) {
            QString label = QString::fromStdString(dataset[i].getDeterminandLabel());
            if (!pollutants.contains(label)) {
                pollutants.append(label);
            }
        }
        return pollutants;
    }
    
    std::vector<std::pair<QString, double>> getTimeSeriesData(const QString& pollutantName) const {
        std::vector<std::pair<QString, double>> data;
        for (int i = 0; i < dataset.size(); ++i) {
            if (QString::fromStdString(dataset[i].getDeterminandLabel()) == pollutantName) {
                data.emplace_back(
                    QString::fromStdString(dataset[i].getSampleDateTime()),
                    dataset[i].getResult()
                );
            }
        }
        return data;
    }
    
    QString getDataPointDetails(const QString& pollutantName, const QString& dateTime) const {
        for (int i = 0; i < dataset.size(); ++i) {
            if (QString::fromStdString(dataset[i].getDeterminandLabel()) == pollutantName &&
                QString::fromStdString(dataset[i].getSampleDateTime()) == dateTime) {
                    return QString(
                        "Purpose: %1\n"
                        "Material Type: %2\n"
                        "Result: %3 %4\n"
                        "Sample Point: %5\n"
                        "Result Interpretation: %6\n"
                        "Is Compliance Sample: %7"
                    )
                    .arg(QString::fromStdString(dataset[i].getPurpose()))
                    .arg(QString::fromStdString(dataset[i].getMaterialType()))
                    .arg(dataset[i].getResult())
                    .arg(QString::fromStdString(dataset[i].getUnit()))
                    .arg(QString::fromStdString(dataset[i].getSamplingPointLabel()))
                    .arg(QString::fromStdString(dataset[i].getResultInterpretation()))
                    .arg(QString::fromStdString(dataset[i].getIsComplianceSample()));
            }
        }
        return QString();
    }
    
    QString getUnitForPollutant(const QString& pollutantName) const {
        for (int i = 0; i < dataset.size(); ++i) {
            if (QString::fromStdString(dataset[i].getDeterminandLabel()) == pollutantName) {
                return QString::fromStdString(dataset[i].getUnit());
            }
        }
        return QString();
    }

private:
    waterQualityDataset dataset;
};