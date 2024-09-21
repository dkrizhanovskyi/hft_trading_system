#ifndef RISK_STRATEGY_H
#define RISK_STRATEGY_H

// Abstract base class for all risk management strategies.
// This class defines an interface for all derived risk strategies, requiring them to implement
// the method `evaluateRisk` to assess the risk level.
class RiskStrategy {
public:
    // Virtual destructor to ensure proper cleanup for derived classes.
    virtual ~RiskStrategy() = default;

    // Method to evaluate the risk level.
    // Should return `false` if the risk is too high, indicating that action must be taken.
    virtual bool evaluateRisk() = 0;
};

#endif // RISK_STRATEGY_H
