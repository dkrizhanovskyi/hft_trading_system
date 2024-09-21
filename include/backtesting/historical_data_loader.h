#ifndef HISTORICAL_DATA_LOADER_H
#define HISTORICAL_DATA_LOADER_H

#include <string>
#include <vector>

// The HistoricalDataLoader class is responsible for loading historical market data from a file.
// This data will be used for backtesting strategies on past market conditions.
class HistoricalDataLoader {
public:
    // Constructor that initializes the loader with a file name.
    // The file should contain historical data for backtesting.
    HistoricalDataLoader(const std::string& fileName);

    // Method to load data from the file.
    // The data is returned as a vector of strings, where each string represents a line from the file.
    std::vector<std::string> loadData();

private:
    // Name of the file containing the historical data.
    std::string fileName_;
};

#endif // HISTORICAL_DATA_LOADER_H
