// src/data_processing/data_collector.cpp

#include "data_collector.h"
#include <iostream>

DataCollector::DataCollector(const std::string& source)
    : source_(source), collecting_(false) {}

void DataCollector::startCollection() {
    collecting_ = true;
    std::cout << "Started collecting data from source: " << source_ << std::endl;
    // Simulated data collection logic
}

void DataCollector::stopCollection() {
    collecting_ = false;
    std::cout << "Stopped collecting data from source: " << source_ << std::endl;
}

bool DataCollector::isCollecting() const {
    return collecting_;
}
