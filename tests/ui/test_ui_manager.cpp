#include <gtest/gtest.h>
#include "ui_manager.h"

// Test to ensure that the UIManager can display the main menu without throwing exceptions
TEST(UITests, CanDisplayMainMenu) {
    // Initialize the UIManager
    UIManager ui;

    // Test that displaying the main menu does not throw any exceptions
    EXPECT_NO_THROW(ui.displayMainMenu());
}

// Test to ensure that the UIManager can handle user input without throwing exceptions
TEST(UITests, CanHandleUserInput) {
    // Initialize the UIManager
    UIManager ui;

    // Test that handling valid user input (option "1") does not throw any exceptions
    EXPECT_NO_THROW(ui.handleUserInput("1"));
}
