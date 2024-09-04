// src/data_processing/data_collector.h

#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <string>

class DataCollector {
public:
    // Constructor to initialize the data source
    DataCollector(const std::string& source);

    // Start collecting data
    void startCollection();

    // Stop collecting data
    void stopCollection();

    // Check if data collection is active
    bool isCollecting() const;

private:
    std::string source_;  // Data source (e.g., market feed)
    bool collecting_;     // Flag indicating whether data collection is active
};

#endif // DATA_COLLECTOR_H
