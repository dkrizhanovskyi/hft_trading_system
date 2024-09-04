#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <string>

// The DataProcessor class is responsible for processing raw data collected by the DataCollector.
// It provides functionality to filter and transform the raw data into a usable format.
class DataProcessor {
public:
    // Process raw data and return processed results.
    // The input is a vector of raw strings, and the output is a vector of processed strings.
    std::vector<std::string> process(const std::vector<std::string>& rawData);

private:
    // Helper function to filter raw data.
    // This could include logic such as removing invalid data points.
    std::string filterData(const std::string& data);

    // Helper function to transform the data.
    // This could include logic for normalizing, formatting, or converting the data.
    std::string transformData(const std::string& data);
};

#endif // DATA_PROCESSOR_H
