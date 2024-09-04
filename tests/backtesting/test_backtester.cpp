#include <gtest/gtest.h>
#include "backtester.h"
#include "historical_data_loader.h"
#include "strategy_manager.h"
#include "data_processor.h"

// Test to verify that the Backtester can run without throwing exceptions.
TEST(BacktesterTests, CanRunBacktest) {
    // Initialize the necessary components for the backtester.
    auto strategyManager = std::make_shared<StrategyManager>();
    auto dataProcessor = std::make_shared<DataProcessor>();
    
    // Initialize the backtester with the strategy manager and data processor.
    Backtester backtester(strategyManager, dataProcessor);

    // Run the backtest and ensure no exceptions are thrown.
    EXPECT_NO_THROW(backtester.runBacktest("/home/kdaniil/Projects/hft_trading_system/build/historical_data.csv"));
}

// Test to ensure that the HistoricalDataLoader can load data correctly.
TEST(BacktesterTests, CanLoadHistoricalData) {
    // Initialize the data loader with a valid file path.
    HistoricalDataLoader loader("/home/kdaniil/Projects/hft_trading_system/build/historical_data.csv");
    
    // Load the data from the file.
    auto data = loader.loadData();
    
    // Ensure that some data points are loaded (non-zero size).
    EXPECT_GT(data.size(), 0);
    
    // Optionally, check that the first data point is not empty (ensure valid data format).
    EXPECT_FALSE(data[0].empty());
}

