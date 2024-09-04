#include "historical_data_loader.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

// Constructor that initializes the HistoricalDataLoader with the given file name.
HistoricalDataLoader::HistoricalDataLoader(const std::string& fileName)
    : fileName_(fileName) {}

// Loads the data from the file.
// Reads each line from the file and stores it in a vector, which is returned.
std::vector<std::string> HistoricalDataLoader::loadData() {
    std::ifstream file(fileName_);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName_);
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);  // Store each line in the vector
    }

    file.close();
    std::cout << "Loaded " << data.size() << " data points from file: " << fileName_ << std::endl;

    return data;
}
