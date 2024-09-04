#include <gtest/gtest.h>
#include "data_processor.h"

// Test to ensure that the DataProcessor can correctly process the raw data.
TEST(DataProcessorTests, CanProcessData) {
    // Initialize the data processor
    DataProcessor processor;

    // Create a vector of raw data strings
    std::vector<std::string> rawData = {"data1", "data2", "data3"};

    // Process the raw data using the processor
    auto processedData = processor.process(rawData);

    // Verify that the processed data has the same size as the raw data
    EXPECT_EQ(processedData.size(), rawData.size());

    // Verify that the first element in the processed data is correctly transformed
    EXPECT_EQ(processedData[0], "Transformed: data1");
}
