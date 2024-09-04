#include <gtest/gtest.h>
#include "risk_manager.h"
#include "max_drawdown_risk_strategy.h"
#include "exposure_limit_risk_strategy.h"

TEST(RiskManagerTests, CanAddRiskStrategy) {
    RiskManager riskManager;
    auto drawdownStrategy = std::make_shared<MaxDrawdownRiskStrategy>(0.2);

    EXPECT_NO_THROW(riskManager.addRiskStrategy(drawdownStrategy));
}

TEST(RiskManagerTests, CanEvaluateRisk) {
    RiskManager riskManager;
    auto exposureStrategy = std::make_shared<ExposureLimitRiskStrategy>(1000000);

    riskManager.addRiskStrategy(exposureStrategy);
    EXPECT_TRUE(riskManager.assessRisk());
}
