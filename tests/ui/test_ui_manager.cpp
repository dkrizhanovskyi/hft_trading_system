#include <gtest/gtest.h>
#include "ui_manager.h"

TEST(UITests, CanDisplayMainMenu) {
    UIManager ui;
    EXPECT_NO_THROW(ui.displayMainMenu());
}

TEST(UITests, CanHandleUserInput) {
    UIManager ui;
    EXPECT_NO_THROW(ui.handleUserInput("1"));  // Ввод для отображения метрик
}
