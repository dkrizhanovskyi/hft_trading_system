// src/strategies/strategy_manager.cpp

#include "strategy_manager.h"

// Adds a strategy to the list of strategies managed by the StrategyManager
void StrategyManager::addStrategy(std::shared_ptr<BaseStrategy> strategy) {
    strategies_.emplace_back(strategy);
}

// Executes all strategies in the list
void StrategyManager::executeStrategies() {
    for (const auto& strategy : strategies_) {
        strategy->execute();
    }
}

// Clears the list of strategies
void StrategyManager::clearStrategies() {
    strategies_.clear();
}
