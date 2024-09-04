// src/backtesting/historical_data_loader.cpp

#include "historical_data_loader.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

HistoricalDataLoader::HistoricalDataLoader(const std::string& fileName)
    : fileName_(fileName) {}

std::vector<std::string> HistoricalDataLoader::loadData() {
    std::ifstream file(fileName_);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName_);
    }

    std::vector<std::string> data;
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }

    file.close();
    std::cout << "Loaded " << data.size() << " data points from file: " << fileName_ << std::endl;

    return data;
}
