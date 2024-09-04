#include "risk_manager.h"

// Adds a risk strategy to the list of strategies managed by the RiskManager.
void RiskManager::addRiskStrategy(std::shared_ptr<RiskStrategy> strategy) {
    riskStrategies_.emplace_back(strategy);
}

// Evaluates all risk strategies. If any strategy reports that the risk is too high (returns false),
// the method will return false immediately. Otherwise, returns true.
bool RiskManager::assessRisk() {
    for (const auto& strategy : riskStrategies_) {
        if (!strategy->evaluateRisk()) {
            return false;  // Stop if any strategy signals high risk
        }
    }
    return true;  // All strategies passed
}

// Clears the list of risk strategies, effectively resetting the manager.
void RiskManager::clearRiskStrategies() {
    riskStrategies_.clear();
}
