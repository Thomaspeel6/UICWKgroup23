#include <algorithm>
#include <numeric>
#include <stdexcept>
#include "dataset.hpp"
#include "csv.hpp"

void WaterQualityDataset::loadData(const std::string& filename)
{
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        waterQuality entry(
            row["id"].get<std::string>(),
            row["samplingPoint"].get<std::string>(),
            row["samplingPointNotation"].get<std::string>(),
            row["samplingPointLabel"].get<std::string>(),
            row["sampleDateTime"].get<std::string>(),
            row["determinandLabel"].get<std::string>(),
            row["determinandDefinition"].get<std::string>(),
            row["determinandNotation"].get<std::string>(),
            row["resultQualifier"].get<std::string>(),
            row["result"].get<std::string>(),
            row["resultInterpretation"].get<std::string>(),
            row["unit"].get<std::string>(),
            row["materialType"].get<std::string>(),
            row["isComplianceSample"].get<std::string>(),
            row["purpose"].get<std::string>(),
            row["easting"].get<std::string>(),
            row["northing"].get<std::string>()
        );
        data.push_back(entry);
    }
}

const waterQuality& WaterQualityDataset::getRow(size_t index) const
{
    return data.at(index);
}

size_t WaterQualityDataset::getSize() const
{
    return data.size();
}

std::pair<std::string, std::string> WaterQualityDataset::calculateStats() const
{
    if (data.empty()) {
        throw std::runtime_error("Dataset is empty. Cannot calculate statistics.");
    }

    std::vector<double> results;
    for (const auto& entry : data) {
        results.push_back(std::stod(entry.getResult()));
    }

    double mean = std::accumulate(results.begin(), results.end(), 0.0) / results.size();
    double highest = *std::max_element(results.begin(), results.end());

    return {std::to_string(mean), std::to_string(highest)};
}
