#ifndef DATA_COLLECTOR_H
#define DATA_COLLECTOR_H

#include <string>

// The DataCollector class is responsible for collecting data from a specified source.
// It allows starting and stopping the data collection process and checks if the collection is active.
class DataCollector {
public:
    // Constructor to initialize the data source.
    // The source parameter represents the origin of the data (e.g., market feed or external API).
    DataCollector(const std::string& source);

    // Start collecting data from the specified source.
    // This method activates the data collection process.
    void startCollection();

    // Stop collecting data.
    // This method deactivates the data collection process.
    void stopCollection();

    // Check if the data collection is currently active.
    // Returns true if the data collection is in progress, false otherwise.
    bool isCollecting() const;

private:
    // Data source (e.g., a market feed or file).
    std::string source_;  

    // Flag indicating whether data collection is currently active.
    bool collecting_;      
};

#endif // DATA_COLLECTOR_H
