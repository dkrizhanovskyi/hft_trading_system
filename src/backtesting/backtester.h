// src/backtesting/backtester.h

#ifndef BACKTESTER_H
#define BACKTESTER_H

#include <string>
#include <memory>
#include "../strategies/strategy_manager.h"
#include "../data_processing/data_processor.h"

class Backtester {
public:
    // Constructor that takes a strategy manager and a data processor
    Backtester(std::shared_ptr<StrategyManager> strategyManager, std::shared_ptr<DataProcessor> dataProcessor);

    // Method to run the backtest on a given file with historical data
    void runBacktest(const std::string& historicalDataFile);

private:
    std::shared_ptr<StrategyManager> strategyManager_;  // Strategy manager to run strategies
    std::shared_ptr<DataProcessor> dataProcessor_;      // Data processor for handling raw data
};

#endif // BACKTESTER_H
