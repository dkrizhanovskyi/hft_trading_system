#include "data_processor.h"
#include <algorithm>  // For data transformations

// Process the raw data by first filtering, then transforming each data point.
// The processed data is returned as a vector of strings.
std::vector<std::string> DataProcessor::process(const std::vector<std::string>& rawData) {
    std::vector<std::string> processedData;
    for (const auto& data : rawData) {
        std::string filtered = filterData(data);
        std::string transformed = transformData(filtered);
        processedData.push_back(transformed);
    }
    return processedData;
}

// Filter the data to remove or modify unwanted elements.
// In this example, no actual filtering is done, but this method can be extended with custom logic.
std::string DataProcessor::filterData(const std::string& data) {
    return data;  // No filtering applied in this simple example
}

// Transform the data, for example by normalizing or formatting it.
// In this example, a simple transformation is applied, appending "Transformed: " to the data.
std::string DataProcessor::transformData(const std::string& data) {
    return "Transformed: " + data;  // Simple transformation for demonstration
}
