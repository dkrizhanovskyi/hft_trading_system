// src/backtesting/historical_data_loader.h

#ifndef HISTORICAL_DATA_LOADER_H
#define HISTORICAL_DATA_LOADER_H

#include <string>
#include <vector>

class HistoricalDataLoader {
public:
    // Constructor takes a filename
    HistoricalDataLoader(const std::string& fileName);

    // Method to load data from the file
    std::vector<std::string> loadData();

private:
    std::string fileName_;  // Name of the file with historical data
};

#endif // HISTORICAL_DATA_LOADER_H
