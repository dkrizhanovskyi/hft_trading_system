#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>

// The UIManager class is responsible for handling the user interface of the application.
// It provides methods to display the main menu and handle user input.
class UIManager {
public:
    // Display the main menu to the user.
    // This method outputs a simple text-based menu for the user to select options.
    void displayMainMenu();

    // Handle the user's input based on the menu selection.
    // Depending on the user's input, this method will trigger different actions such as viewing metrics or executing strategies.
    void handleUserInput(const std::string& input);

private:
    // Private method to display system metrics.
    // This method could be connected to the Monitor class to display real-time system metrics.
    void displayMetrics();

    // Private method to execute a trading strategy.
    // Takes the name of the strategy as a parameter and simulates its execution.
    // In a real application, this would trigger the actual strategy execution logic.
    void executeStrategy(const std::string& strategyName);
};

#endif // UI_MANAGER_H
