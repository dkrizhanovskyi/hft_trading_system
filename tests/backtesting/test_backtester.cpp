#include <gtest/gtest.h>
#include "backtester.h"
#include "historical_data_loader.h"
#include "strategy_manager.h"
#include "data_processor.h"


TEST(BacktesterTests, CanRunBacktest) {
    auto strategyManager = std::make_shared<StrategyManager>();
    auto dataProcessor = std::make_shared<DataProcessor>();
    Backtester backtester(strategyManager, dataProcessor);

    EXPECT_NO_THROW(backtester.runBacktest("/home/kdaniil/Projects/hft_trading_system/build/historical_data.csv"));
}

TEST(BacktesterTests, CanLoadHistoricalData) {
    HistoricalDataLoader loader("/home/kdaniil/Projects/hft_trading_system/build/historical_data.csv");
    auto data = loader.loadData();
    
    EXPECT_GT(data.size(), 0);  // Должны загрузиться данные
}
