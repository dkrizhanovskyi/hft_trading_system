// src/risk_manager.h

#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include <vector>
#include <memory>
#include "risk_strategy.h"

// Class that manages multiple risk strategies
class RiskManager {
public:
    // Add a new risk strategy to the manager
    void addRiskStrategy(std::shared_ptr<RiskStrategy> strategy);

    // Evaluate all risk strategies, returning false if any strategy signals a risk
    bool assessRisk();

    // Remove all risk strategies
    void clearRiskStrategies();

private:
    // Vector to store the risk strategies
    std::vector<std::shared_ptr<RiskStrategy>> riskStrategies_;
};

#endif // RISK_MANAGER_H
