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
#include "security.h"  // Подключаем модуль безопасности для шифрования и подписей
#include <iostream>
#include <memory>
#include <openssl/aes.h>  // For AES encryption

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
    auto drawdownStrategy = std::make_shared<MaxDrawdownRiskStrategy>(0.2);
    auto exposureStrategy = std::make_shared<ExposureLimitRiskStrategy>(1000000);
    riskManager.addRiskStrategy(drawdownStrategy);
    riskManager.addRiskStrategy(exposureStrategy);

    // Initialize Backtester
    Backtester backtester(strategyManager, dataProcessor);

    uint8_t key[AES_BLOCK_SIZE] = { };
    encryption_result_t encrypted_log;

    // Main loop for user interaction
    std::string userInput;
    while (true) {
        uiManager.displayMainMenu();
        std::cin >> userInput;

        if (userInput == "3") {
            break;
        }

        uiManager.handleUserInput(userInput);

        if (userInput == "1") {
            // View Metrics
            logger.log("User viewed metrics.");
            monitor.addMetric("Metric1", 100.0);
            monitor.reportMetrics();
        } else if (userInput == "2") {
            // Execute Backtest
            std::string dataFile = "historical_data.csv";
            backtester.runBacktest(dataFile);

            encryption_result_t signature;
            int ret = sign_data((const uint8_t *)dataFile.c_str(), dataFile.size(), key, sizeof(key), &signature);
            if (ret == 0) {
                std::cout << "Backtest results signed successfully. Signature: ";
                for (size_t i = 0; i < signature.data_len; ++i) {
                    printf("%02x", signature.data[i]);
                }
                std::cout << std::endl;
            } else {
                std::cerr << "Failed to sign the backtest results." << std::endl;
            }

            encryption_result_free(&signature);  
            logger.log("User executed a strategy.");
        } else {
            std::cout << "Invalid option, please try again." << std::endl;
        }
    }

    int ret = aes_encrypt((const uint8_t *)"Trading system shutdown", 22, key, AES_BLOCK_SIZE, &encrypted_log);
    if (ret == 0) {
        logger.log("Encrypted log: ");
        for (size_t i = 0; i < encrypted_log.data_len; ++i) {
            printf("%02x", encrypted_log.data[i]);
        }
        std::cout << std::endl;
    } else {
        std::cerr << "Failed to encrypt log message." << std::endl;
    }
    
    encryption_result_free(&encrypted_log);
    logger.log("Trading system shutdown.");
    return 0;
}
