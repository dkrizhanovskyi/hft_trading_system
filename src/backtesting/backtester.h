#ifndef BACKTESTER_H
#define BACKTESTER_H

#include <string>
#include <memory>
#include "../strategies/strategy_manager.h"
#include "../data_processing/data_processor.h"

// The Backtester class is responsible for running backtests on historical data.
// It uses the strategy manager to execute strategies and the data processor to handle raw data.
class Backtester {
public:
    // Constructor that takes a strategy manager and a data processor.
    // These components are required for executing strategies and processing historical data.
    Backtester(std::shared_ptr<StrategyManager> strategyManager, std::shared_ptr<DataProcessor> dataProcessor);

    // Method to run the backtest on a given file with historical data.
    // It loads, processes the data, and applies strategies to the historical data points.
    void runBacktest(const std::string& historicalDataFile);

private:
    std::shared_ptr<StrategyManager> strategyManager_;  // Manages the execution of trading strategies
    std::shared_ptr<DataProcessor> dataProcessor_;      // Handles the processing of raw historical data
};

#endif // BACKTESTER_H
