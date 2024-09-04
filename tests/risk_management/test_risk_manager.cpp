#include <gtest/gtest.h>
#include "risk_manager.h"
#include "max_drawdown_risk_strategy.h"
#include "exposure_limit_risk_strategy.h"

// Test to ensure that a risk strategy can be added to the RiskManager without throwing exceptions
TEST(RiskManagerTests, CanAddRiskStrategy) {
    // Initialize RiskManager
    RiskManager riskManager;

    // Create a MaxDrawdownRiskStrategy with a 20% maximum drawdown
    auto drawdownStrategy = std::make_shared<MaxDrawdownRiskStrategy>(0.2);

    // Test that adding the strategy does not throw an exception
    EXPECT_NO_THROW(riskManager.addRiskStrategy(drawdownStrategy));
}

// Test to ensure that the RiskManager can evaluate risk and return a valid result
TEST(RiskManagerTests, CanEvaluateRisk) {
    // Initialize RiskManager
    RiskManager riskManager;

    // Create an ExposureLimitRiskStrategy with a 1M maximum exposure
    auto exposureStrategy = std::make_shared<ExposureLimitRiskStrategy>(1000000);

    // Add the exposure limit risk strategy to the RiskManager
    riskManager.addRiskStrategy(exposureStrategy);

    // Test that assessing risk returns true (i.e., risk is within acceptable limits)
    EXPECT_TRUE(riskManager.assessRisk());
}
