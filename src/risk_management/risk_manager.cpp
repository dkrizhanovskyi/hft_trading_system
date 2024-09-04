// src/risk_manager.cpp

#include "risk_manager.h"

// Adds a risk strategy to the list
void RiskManager::addRiskStrategy(std::shared_ptr<RiskStrategy> strategy) {
    riskStrategies_.emplace_back(strategy);
}

// Evaluate all risk strategies
bool RiskManager::assessRisk() {
    for (const auto& strategy : riskStrategies_) {
        if (!strategy->evaluateRisk()) {
            return false; // If any strategy reports a high risk, return false
        }
    }
    return true; // All strategies have passed
}

// Clears all risk strategies
void RiskManager::clearRiskStrategies() {
    riskStrategies_.clear();
}
