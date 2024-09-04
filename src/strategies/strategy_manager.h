#ifndef STRATEGY_MANAGER_H
#define STRATEGY_MANAGER_H

#include <vector>
#include <memory>
#include "base_strategy.h"

// Class that manages a collection of trading strategies.
// This class allows adding, executing, and clearing a group of trading strategies.
// It acts as a central controller to manage multiple strategy instances.
class StrategyManager {
public:
    // Add a new strategy to the manager.
    // The strategy is passed as a shared pointer, allowing for efficient memory management.
    // Strategies can be dynamically added and managed without worrying about manual memory cleanup.
    void addStrategy(std::shared_ptr<BaseStrategy> strategy);

    // Execute all registered strategies.
    // This function iterates through all stored strategies and calls their `execute` method.
    // This allows multiple strategies to be run in sequence.
    void executeStrategies();

    // Remove all strategies from the manager.
    // This clears the internal vector, removing all registered strategies and freeing the associated resources.
    void clearStrategies();

private:
    // Vector to store the strategies.
    // The vector holds shared pointers to BaseStrategy objects, allowing multiple strategies
    // to coexist and be managed dynamically.
    std::vector<std::shared_ptr<BaseStrategy>> strategies_;
};

#endif // STRATEGY_MANAGER_H
