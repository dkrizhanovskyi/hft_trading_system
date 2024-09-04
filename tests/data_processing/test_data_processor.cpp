#include <gtest/gtest.h>
#include "data_processor.h"

TEST(DataProcessorTests, CanProcessData) {
    DataProcessor processor;
    std::vector<std::string> rawData = {"data1", "data2", "data3"};
    auto processedData = processor.process(rawData);

    EXPECT_EQ(processedData.size(), rawData.size());
    EXPECT_EQ(processedData[0], "Transformed: data1");
}
