// src/risk_strategy.h

#ifndef RISK_STRATEGY_H
#define RISK_STRATEGY_H

// Abstract base class for all risk management strategies
class RiskStrategy {
public:
    virtual ~RiskStrategy() = default;

    // Method to evaluate the risk level, should return false if risk is too high
    virtual bool evaluateRisk() = 0;
};

#endif // RISK_STRATEGY_H
