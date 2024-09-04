// src/strategies/base_strategy.h

#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <string>

// Base class for all trading strategies
class BaseStrategy {
public:
    // Virtual destructor to ensure proper cleanup for derived classes
    virtual ~BaseStrategy() = default;

    // Method to execute the strategy
    virtual void execute() = 0;

    // Optional: Method to configure the strategy with necessary parameters
    virtual void configure(const std::string& config) = 0;

    // Optional: Analyze the results after the strategy has been executed
    virtual std::string analyzeResults() const = 0;
};

#endif // BASE_STRATEGY_H
