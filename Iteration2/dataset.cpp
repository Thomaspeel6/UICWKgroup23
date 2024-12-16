#include <algorithm>
#include <numeric>
#include <stdexcept>

#include "dataset.hpp"
#include "csv.hpp"

void waterQualityDataset::loadData(const std::string& filename)
{
    csv::CSVReader reader(filename);

    this->data.clear();

    for (const auto& row : reader) {
        waterQuality entry(
            row["@id"].get<std::string>(),
            row["sample.samplingPoint"].get<std::string>(),
            row["sample.samplingPoint.notation"].get<std::string>(),
            row["sample.samplingPoint.label"].get<std::string>(),
            row["sample.sampleDateTime"].get<std::string>(),
            row["determinand.label"].get<std::string>(),
            row["determinand.definition"].get<std::string>(),
            row["determinand.notation"].get<std::string>(),
            row["resultQualifier.notation"].get<std::string>(),
            row["result"].get<std::string>(),
            row["codedResultInterpretation.interpretation"].get<std::string>(),
            row["determinand.unit.label"].get<std::string>(),
            row["sample.sampledMaterialType.label"].get<std::string>(),
            row["sample.isComplianceSample"].get<std::string>(),
            row["sample.purpose.label"].get<std::string>(),
            row["sample.samplingPoint.easting"].get<std::string>(),
            row["sample.samplingPoint.northing"].get<std::string>()
        );

        this->data.push_back(entry);
    }

}

const waterQuality& waterQualityDataset::getRow(size_t index) const
{
    return this->data.at(index);

}

size_t waterQualityDataset::getSize() const
{
    return this->data.size();
}

std::pair<std::string, std::string> waterQualityDataset::calculateStats() const
{
    if (this->data.empty()) {
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
