#ifndef MAX_DRAWDOWN_RISK_STRATEGY_H
#define MAX_DRAWDOWN_RISK_STRATEGY_H

#include "risk_strategy.h"

// Strategy to monitor and manage drawdown risk.
// This strategy triggers a risk signal if the current drawdown exceeds the maximum allowable drawdown.
class MaxDrawdownRiskStrategy : public RiskStrategy {
public:
    // Constructor that accepts the maximum allowed drawdown.
    MaxDrawdownRiskStrategy(double maxAllowedDrawdown);

    // Evaluate the risk based on the current drawdown level.
    // Returns `false` if the drawdown exceeds the allowed threshold.
    bool evaluateRisk() override;

    // Method to update the current drawdown value.
    void updateDrawdown(double currentDrawdown);

private:
    double maxAllowedDrawdown_;  // Maximum allowable drawdown before triggering risk.
    double currentDrawdown_;     // Current drawdown of the system.
};

#endif // MAX_DRAWDOWN_RISK_STRATEGY_H
