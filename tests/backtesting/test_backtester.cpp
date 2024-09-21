#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>  // For std::remove
#include "backtester.h"
#include "historical_data_loader.h"
#include "strategy_manager.h"
#include "data_processor.h"

// Helper function to create a dummy historical data CSV file for testing
void createHistoricalDataFile(const std::string& filepath) {
    std::ofstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to create file: " + filepath);
    }
    // Writing some dummy data (adjust as per the real format expected by the Backtester)
    file << "Date,Price,Volume\n";
    file << "2023-09-20,100,200\n";
    file << "2023-09-21,105,250\n";
    file.close();
}

// Test suite for Backtester
class BacktesterTests : public ::testing::Test {
protected:
    std::string filepath;

    // Set up before each test
    void SetUp() override {
        filepath = "/tmp/historical_data.csv";  // Temporary file location
        createHistoricalDataFile(filepath);  // Create the file
    }

    // Clean up after each test
    void TearDown() override {
        std::remove(filepath.c_str());  // Remove the file
    }
};

// Test to verify that the Backtester can run without throwing exceptions.
TEST_F(BacktesterTests, CanRunBacktest) {
    // Initialize the necessary components for the backtester.
    auto strategyManager = std::make_shared<StrategyManager>();
    auto dataProcessor = std::make_shared<DataProcessor>();

    // Initialize the backtester with the strategy manager and data processor.
    Backtester backtester(strategyManager, dataProcessor);

    // Run the backtest and ensure no exceptions are thrown.
    EXPECT_NO_THROW(backtester.runBacktest(filepath));
}

// Test to ensure that the HistoricalDataLoader can load data correctly.
TEST_F(BacktesterTests, CanLoadHistoricalData) {
    // Initialize the data loader with the test file path.
    HistoricalDataLoader loader(filepath);

    // Load the data from the file.
    auto data = loader.loadData();

    // Ensure that some data points are loaded (non-zero size).
    EXPECT_GT(data.size(), 0);

    // Optionally, check that the first data point is not empty (ensure valid data format).
    EXPECT_FALSE(data[0].empty());
}
