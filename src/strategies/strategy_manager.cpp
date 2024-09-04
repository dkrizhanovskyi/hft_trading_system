#include "strategy_manager.h"

// Adds a strategy to the list of strategies managed by the StrategyManager.
// The strategy is stored as a shared pointer to ensure that memory is managed automatically,
// and multiple references to the same strategy can exist if needed.
void StrategyManager::addStrategy(std::shared_ptr<BaseStrategy> strategy) {
    strategies_.emplace_back(strategy);
}

// Executes all strategies in the list.
// This method loops through the vector of strategies and calls the `execute` method on each one.
// It allows multiple strategies to be executed in sequence.
void StrategyManager::executeStrategies() {
    for (const auto& strategy : strategies_) {
        strategy->execute();
    }
}

// Clears the list of strategies.
// This method removes all strategies from the internal vector, effectively releasing any resources
// held by the strategies and allowing new strategies to be added later.
void StrategyManager::clearStrategies() {
    strategies_.clear();
}
