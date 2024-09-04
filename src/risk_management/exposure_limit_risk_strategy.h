// src/risk/exposure_limit_risk_strategy.h

#ifndef EXPOSURE_LIMIT_RISK_STRATEGY_H
#define EXPOSURE_LIMIT_RISK_STRATEGY_H

#include "risk_strategy.h"

// Strategy to monitor exposure limits
class ExposureLimitRiskStrategy : public RiskStrategy {
public:
    // Constructor to set the maximum allowed exposure
    ExposureLimitRiskStrategy(double maxAllowedExposure);

    // Evaluate the risk based on the current exposure level
    bool evaluateRisk() override;

    // Method to update the current exposure level
    void updateExposure(double currentExposure);

private:
    double maxAllowedExposure_;  // Maximum allowable exposure
    double currentExposure_;     // Current exposure of the system
};

#endif // EXPOSURE_LIMIT_RISK_STRATEGY_H
