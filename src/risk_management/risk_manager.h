#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include <vector>
#include <memory>
#include "risk_strategy.h"

// Class that manages multiple risk strategies.
// This class allows adding different risk strategies and evaluating them as a group.
class RiskManager {
public:
    // Add a new risk strategy to the manager.
    // Each risk strategy is passed as a shared pointer, allowing for flexible memory management.
    void addRiskStrategy(std::shared_ptr<RiskStrategy> strategy);

    // Evaluate all registered risk strategies.
    // Returns `false` if any strategy signals a high risk, stopping further evaluation.
    bool assessRisk();

    // Remove all risk strategies.
    // Clears the list of strategies, effectively resetting the risk manager.
    void clearRiskStrategies();

private:
    // Vector to store the risk strategies.
    std::vector<std::shared_ptr<RiskStrategy>> riskStrategies_;
};

#endif // RISK_MANAGER_H
