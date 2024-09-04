// src/risk/max_drawdown_risk_strategy.h

#ifndef MAX_DRAWDOWN_RISK_STRATEGY_H
#define MAX_DRAWDOWN_RISK_STRATEGY_H

#include "risk_strategy.h"

// Strategy to monitor and manage drawdown risk
class MaxDrawdownRiskStrategy : public RiskStrategy {
public:
    // Constructor that accepts the max allowed drawdown
    MaxDrawdownRiskStrategy(double maxAllowedDrawdown);

    // Evaluate the risk based on current drawdown level
    bool evaluateRisk() override;

    // Method to update current drawdown values
    void updateDrawdown(double currentDrawdown);

private:
    double maxAllowedDrawdown_;  // Maximum allowable drawdown
    double currentDrawdown_;     // Current drawdown of the system
};

#endif // MAX_DRAWDOWN_RISK_STRATEGY_H
