#include <gtest/gtest.h>
#include "scalping_strategy.h"

TEST(ScalpingStrategyTests, CanConfigureStrategy) {
    ScalpingStrategy strategy;
    EXPECT_NO_THROW(strategy.configure("Config for scalping"));
}

TEST(ScalpingStrategyTests, CanExecuteStrategy) {
    ScalpingStrategy strategy;
    strategy.execute();
    EXPECT_EQ(strategy.analyzeResults(), "Scalping strategy executed 1 trades.");
}
