// src/ui/ui_manager.h

#ifndef UI_MANAGER_H
#define UI_MANAGER_H

#include <string>

class UIManager {
public:
    // Display the main menu to the user
    void displayMainMenu();

    // Handle the user's input based on menu selection
    void handleUserInput(const std::string& input);

private:
    // Example private methods for handling specific options
    void displayMetrics();
    void executeStrategy(const std::string& strategyName);
};

#endif // UI_MANAGER_H
