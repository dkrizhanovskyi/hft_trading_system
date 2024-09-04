// src/ui/ui_manager.cpp

#include "ui_manager.h"
#include <iostream>

void UIManager::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. View Metrics\n";
    std::cout << "2. Execute Strategy\n";
    std::cout << "3. Exit\n";
}

void UIManager::handleUserInput(const std::string& input) {
    if (input == "1") {
        displayMetrics();
    } else if (input == "2") {
        std::string strategyName;
        std::cout << "Enter strategy name: ";
        std::cin >> strategyName;
        executeStrategy(strategyName);
    } else if (input == "3") {
        std::cout << "Exiting...\n";
    } else {
        std::cout << "Invalid option, please try again.\n";
    }
}

void UIManager::displayMetrics() {
    // Simulate displaying metrics (could be replaced by actual monitoring)
    std::cout << "Displaying system metrics...\n";
    // Example: You can call the Monitor class here to display metrics
}

void UIManager::executeStrategy(const std::string& strategyName) {
    // Simulate executing a strategy (this would call the actual strategy execution logic)
    std::cout << "Executing strategy: " << strategyName << "\n";
    // Example: You could call StrategyManager here to execute the selected strategy
}
