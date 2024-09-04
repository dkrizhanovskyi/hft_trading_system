#include "ui_manager.h"
#include <iostream>  // For console input/output

// Display the main menu to the user.
// This method outputs a text-based menu with options for the user to choose.
void UIManager::displayMainMenu() {
    std::cout << "Main Menu:\n";
    std::cout << "1. View Metrics\n";
    std::cout << "2. Execute Strategy\n";
    std::cout << "3. Exit\n";
}

// Handle user input based on their menu selection.
// Depending on the input, the method will either display metrics, execute a strategy, or exit the application.
void UIManager::handleUserInput(const std::string& input) {
    if (input == "1") {
        displayMetrics();  // Show system metrics
    } else if (input == "2") {
        std::string strategyName;
        std::cout << "Enter strategy name: ";
        std::cin >> strategyName;
        executeStrategy(strategyName);  // Execute the specified strategy
    } else if (input == "3") {
        std::cout << "Exiting...\n";
    } else {
        std::cout << "Invalid option, please try again.\n";
    }
}

// Display system metrics.
// This method simulates the display of system metrics. In a full implementation, this could call the Monitor class to fetch real-time metrics.
void UIManager::displayMetrics() {
    std::cout << "Displaying system metrics...\n";
    // Example: You can call the Monitor class here to display actual metrics
}

// Execute the specified strategy.
// This method simulates strategy execution by outputting the strategy name.
// In a real application, this could invoke the StrategyManager to execute the selected trading strategy.
void UIManager::executeStrategy(const std::string& strategyName) {
    std::cout << "Executing strategy: " << strategyName << "\n";
    // Example: Call StrategyManager here to execute the strategy
}
