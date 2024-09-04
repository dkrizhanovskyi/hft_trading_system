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
    // The UIManager handles user interactions, displaying the menu and handling input.
    UIManager uiManager;

    // Initialize Logger and Monitor
    // The Logger logs system events to a file, while the Monitor tracks and displays system metrics.
    Logger logger("system_log.txt");
    Monitor monitor;

    // Initialize Strategy Manager and add strategies
    // StrategyManager manages the execution of trading strategies.
    auto strategyManager = std::make_shared<StrategyManager>();
    auto scalpingStrategy = std::make_shared<ScalpingStrategy>();
    auto meanReversionStrategy = std::make_shared<MeanReversionStrategy>();
    strategyManager->addStrategy(scalpingStrategy);  // Adding a scalping strategy
    strategyManager->addStrategy(meanReversionStrategy);  // Adding a mean reversion strategy

    // Initialize Data Processor
    // The DataProcessor is used to handle raw historical data for backtesting.
    auto dataProcessor = std::make_shared<DataProcessor>();

    // Initialize Risk Manager and add risk strategies
    // RiskManager evaluates the risk levels using various risk strategies.
    RiskManager riskManager;
    auto drawdownStrategy = std::make_shared<MaxDrawdownRiskStrategy>(0.2);  // Maximum drawdown allowed: 20%
    auto exposureStrategy = std::make_shared<ExposureLimitRiskStrategy>(1000000);  // Maximum exposure allowed: 1M
    riskManager.addRiskStrategy(drawdownStrategy);
    riskManager.addRiskStrategy(exposureStrategy);

    // Initialize Backtester
    // The Backtester uses the StrategyManager and DataProcessor to run strategies on historical data.
    Backtester backtester(strategyManager, dataProcessor);

    // Main loop for user interaction
    // The loop continues to display the main menu and handle user input until the user exits.
    std::string userInput;
    while (true) {
        // Display the main menu to the user
        uiManager.displayMainMenu();
        std::cin >> userInput;

        // Exit the loop if the user selects the "Exit" option
        if (userInput == "3") {
            break;
        }

        // Handle the user's input (e.g., view metrics or execute a strategy)
        uiManager.handleUserInput(userInput);

        if (userInput == "1") {
            // View Metrics (example of logging and monitoring)
            // Log the action and display system metrics via the Monitor
            logger.log("User viewed metrics.");
            monitor.addMetric("Metric1", 100.0);  // Example metric
            monitor.reportMetrics();  // Display the metrics
        } else if (userInput == "2") {
            // Execute Backtest (execute strategy)
            // Log the action and run a backtest on the historical data file
            std::string dataFile = "historical_data.csv";
            backtester.runBacktest(dataFile);

            logger.log("User executed a strategy.");
        } else {
            // Handle invalid input
            std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    // Log system shutdown
    logger.log("Trading system shutdown.");
    return 0;
}
