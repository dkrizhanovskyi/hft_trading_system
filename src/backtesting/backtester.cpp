#include "backtester.h"
#include "historical_data_loader.h"
#include <iostream>

// Constructor that initializes the Backtester with the strategy manager and data processor.
Backtester::Backtester(std::shared_ptr<StrategyManager> strategyManager, std::shared_ptr<DataProcessor> dataProcessor)
    : strategyManager_(strategyManager), dataProcessor_(dataProcessor) {}

// Runs the backtest by loading historical data from the file and processing it.
// The processed data is then used to execute the strategies.
void Backtester::runBacktest(const std::string& historicalDataFile) {
    HistoricalDataLoader loader(historicalDataFile);
    auto rawData = loader.loadData();
    auto processedData = dataProcessor_->process(rawData);

    std::cout << "Running backtest on data from file: " << historicalDataFile << std::endl;

    // Execute strategies on each processed data point
    for ([[maybe_unused]] const auto& data : processedData) {
        strategyManager_->executeStrategies();
    }

    std::cout << "Backtest completed." << std::endl;
}
