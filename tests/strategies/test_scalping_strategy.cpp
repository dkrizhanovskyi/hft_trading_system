#include <gtest/gtest.h>
#include "scalping_strategy.h"

// Test to ensure that the ScalpingStrategy can be configured without throwing exceptions
TEST(ScalpingStrategyTests, CanConfigureStrategy) {
    // Initialize the scalping strategy
    ScalpingStrategy strategy;

    // Test that configuring the strategy does not throw an exception
    EXPECT_NO_THROW(strategy.configure("Config for scalping"));
}

// Test to ensure that the ScalpingStrategy can execute and analyze results correctly
TEST(ScalpingStrategyTests, CanExecuteStrategy) {
    // Initialize the scalping strategy
    ScalpingStrategy strategy;

    // Execute the strategy once
    strategy.execute();

    // Test that the strategy reports 1 trade executed
    EXPECT_EQ(strategy.analyzeResults(), "Scalping strategy executed 1 trades.");
}
