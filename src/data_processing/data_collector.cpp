#include "data_collector.h"
#include <iostream>

// Constructor to initialize the data source and set the initial collection state to false (inactive).
DataCollector::DataCollector(const std::string& source)
    : source_(source), collecting_(false) {}

// Start the data collection process and indicate that data is now being collected.
void DataCollector::startCollection() {
    collecting_ = true;
    std::cout << "Started collecting data from source: " << source_ << std::endl;
    // Simulated data collection logic can be added here.
}

// Stop the data collection process and set the collecting flag to false.
void DataCollector::stopCollection() {
    collecting_ = false;
    std::cout << "Stopped collecting data from source: " << source_ << std::endl;
}

// Return the current status of data collection (true if active, false if inactive).
bool DataCollector::isCollecting() const {
    return collecting_;
}
