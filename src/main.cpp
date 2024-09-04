#include "ui_manager.h"
#include "strategy_manager.h"
#include "scalping_strategy.h"
#include "mean_reversion_strategy.h"
#include "data_processor.h"
#include "risk_manager.h"
#include "max_drawdown_risk_strategy.h"
#include "exposure_limit_risk_strategy.h"
#include "backtester.h"
#include "logger.h"
#include "monitor.h"
#include <iostream>
#include <memory>

int main() {
    // Initialize UI Manager
    UIManager uiManager;

    // Initialize Logger and Monitor
    Logger logger("system_log.txt");
    Monitor monitor;

    // Initialize Strategy Manager and add strategies
    auto strategyManager = std::make_shared<StrategyManager>();
    auto scalpingStrategy = std::make_shared<ScalpingStrategy>();
    auto meanReversionStrategy = std::make_shared<MeanReversionStrategy>();
    strategyManager->addStrategy(scalpingStrategy);
    strategyManager->addStrategy(meanReversionStrategy);

    // Initialize Data Processor
    auto dataProcessor = std::make_shared<DataProcessor>();

    // Initialize Risk Manager and add risk strategies
    RiskManager riskManager;
    auto drawdownStrategy = std::make_shared<MaxDrawdownRiskStrategy>(0.2);  // 20% max drawdown
    auto exposureStrategy = std::make_shared<ExposureLimitRiskStrategy>(1000000);  // 1M max exposure
    riskManager.addRiskStrategy(drawdownStrategy);
    riskManager.addRiskStrategy(exposureStrategy);

    // Initialize Backtester
    Backtester backtester(strategyManager, dataProcessor);

    // Main loop for user interaction
    std::string userInput;
    while (true) {
        // Display the main menu
        uiManager.displayMainMenu();
        std::cin >> userInput;

        if (userInput == "3") {
            break;  // Exit the program
        }

        uiManager.handleUserInput(userInput);

        if (userInput == "1") {
            // View Metrics (example of logging and monitoring)
            logger.log("User viewed metrics.");
            monitor.addMetric("Metric1", 100.0);  // Example metric
            monitor.reportMetrics();
        } else if (userInput == "2") {
            // Execute Backtest (execute strategy)
            std::string dataFile = "historical_data.csv";
            backtester.runBacktest(dataFile);

            logger.log("User executed a strategy.");
        } else {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    logger.log("Trading system shutdown.");
    return 0;
}
