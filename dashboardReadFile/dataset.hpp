#pragma once

#include <vector>
#include "waterquality.hpp"

class waterQualityDataset
{
  public:
    waterQualityDataset() {}
    waterQualityDataset(const std::string& filename) { loadData(filename); }
    void loadData(const std::string&);
    int size() const { return data.size(); }
    waterQuality operator[](int index) const { return data.at(index); }

/*  waterQuality highestResult() const;
    waterQuality lowestResult() const;
    double meanResult() const;  */

  private:
    std::vector<waterQuality> data;
    void checkDataExists() const;
};
