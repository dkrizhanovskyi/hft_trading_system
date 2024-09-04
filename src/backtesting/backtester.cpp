#include "backtester.h"
#include "historical_data_loader.h"
#include <iostream>
#include <future>  // Для асинхронного выполнения

// Constructor that initializes the Backtester with the strategy manager and data processor.
Backtester::Backtester(std::shared_ptr<StrategyManager> strategyManager, std::shared_ptr<DataProcessor> dataProcessor)
    : strategyManager_(strategyManager), dataProcessor_(dataProcessor) {}

// Runs the backtest by loading historical data from the file and processing it.
// The processed data is then used to execute the strategies.
void Backtester::runBacktest(const std::string& historicalDataFile) {
    HistoricalDataLoader loader(historicalDataFile);

    // Асинхронная загрузка данных
    auto futureRawData = std::async(std::launch::async, [&loader]() {
        return loader.loadData();
    });

    // Ждём загрузки данных
    auto rawData = futureRawData.get();

    // Асинхронная обработка данных
    auto futureProcessedData = std::async(std::launch::async, [this, &rawData]() {
        return dataProcessor_->process(rawData);
    });

    auto processedData = futureProcessedData.get();

    std::cout << "Running backtest on data from file: " << historicalDataFile << std::endl;

    // Параллельное выполнение стратегий на каждом наборе данных
    std::vector<std::future<void>> futures;
    for (const auto& data : processedData) {
        futures.push_back(std::async(std::launch::async, [this]() {
            strategyManager_->executeStrategies();
        }));
    }

    // Ожидаем завершения всех стратегий
    for (auto& future : futures) {
        future.get();
    }

    std::cout << "Backtest completed." << std::endl;
}
