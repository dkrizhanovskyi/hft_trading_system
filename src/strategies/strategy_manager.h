// src/strategies/strategy_manager.h

#ifndef STRATEGY_MANAGER_H
#define STRATEGY_MANAGER_H

#include <vector>
#include <memory>
#include "base_strategy.h"

// Class that manages a collection of trading strategies
class StrategyManager {
public:
    // Add a new strategy to the manager
    void addStrategy(std::shared_ptr<BaseStrategy> strategy);

    // Execute all registered strategies
    void executeStrategies();

    // Remove all strategies
    void clearStrategies();

private:
    // Vector to store the strategies
    std::vector<std::shared_ptr<BaseStrategy>> strategies_;
};

#endif // STRATEGY_MANAGER_H
