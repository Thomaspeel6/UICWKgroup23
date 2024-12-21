#ifndef DATASET_HPP
#define DATASET_HPP

#include <vector>
#include <string>
#include "waterquality.hpp"

class waterQualityDataset {
public:
    // Load data from a CSV file into the dataset
    void loadData(const std::string& filename);

    // Retrieve a specific waterQuality entry by index
    const waterQuality& getRow(size_t index) const;

    // Get the total number of entries in the dataset
    size_t getSize() const;

    const std::vector<waterQuality>& getData() const { return data; }

    // Calculate statistics: mean and highest result
    std::pair<std::string, std::string> calculateStats() const;

private:
    std::vector<waterQuality> data; // Stores waterQuality objects
};

#endif // DATASET_HPP
