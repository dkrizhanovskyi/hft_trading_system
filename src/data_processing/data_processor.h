// src/data_processing/data_processor.h

#ifndef DATA_PROCESSOR_H
#define DATA_PROCESSOR_H

#include <vector>
#include <string>

class DataProcessor {
public:
    // Process raw data and return processed results
    std::vector<std::string> process(const std::vector<std::string>& rawData);

private:
    // Helper functions to filter and transform data
    std::string filterData(const std::string& data);
    std::string transformData(const std::string& data);
};

#endif // DATA_PROCESSOR_H
