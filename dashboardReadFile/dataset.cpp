#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"

using namespace std;

void waterQualityDataset::loadData(const string& filename)
{
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row: reader) {
        waterQuality quality{
            row["@id"].get<>(),
            row["sample.samplingPoint"].get<>(),
            row["sample.samplingPoint.notation"].get<>(),
            row["sample.samplingPoint.label"].get<>(),
            row["sample.sampleDateTime"].get<>(),
            row["determinand.label"].get<>(),
            row["determinand.definition"].get<>(),
            row["determinand.notation"].get<>(),
            row["resultQualifier.notation"].get<>(),
            //row["result"].get<double>(),
            row["result"].get<>(),
            row["codedResultInterpretation.interpretation"].get<>(),
            row["determinand.unit.label"].get<>(),
            row["sample.sampledMaterialType.label"].get<>(),
            //row["sample.isComplianceSample"].get<bool>(),
            row["sample.isComplianceSample"].get<>(),
            row["sample.purpose.label"].get<>(),
            //row["sample.samplingPoint.easting"].get<int>(),
            //row["sample.samplingPoint.northing"].get<int>()
            row["sample.samplingPoint.easting"].get<>(),
            row["sample.samplingPoint.northing"].get<>()
        };
        data.push_back(quality);
    }
}

/*
waterQuality waterQualityDataset::highestResult() const
{
    checkDataExists();

    auto quality = max_element(data.begin(), data.end(),
        [](waterQuality a, waterQuality b) { 
            return a.getResult() < b.getResult(); 
        });

    return *quality;
}

waterQuality waterQualityDataset::lowestResult() const
{
    checkDataExists();

    auto quality = min_element(data.begin(), data.end(),
        [](waterQuality a, waterQuality b) { 
            return a.getResult() < b.getResult(); 
        });

    return *quality;
}

double waterQualityDataset::meanResult() const
{
    checkDataExists();

    auto sum = accumulate(data.begin(), data.end(), 0.0,
        [](double total, waterQuality q) { 
            return total + q.getResult(); 
        });

    return sum / data.size();
}
*/
void waterQualityDataset::checkDataExists() const
{
    if (size() == 0) {
        throw runtime_error("Dataset is empty!");
    }
}
