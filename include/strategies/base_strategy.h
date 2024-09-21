#ifndef BASE_STRATEGY_H
#define BASE_STRATEGY_H

#include <string>

// Base class for all trading strategies
// This class serves as an abstract interface for all trading strategies.
// Derived classes must implement the methods to execute, configure, and analyze their specific strategies.
class BaseStrategy {
public:
    // Virtual destructor to ensure proper cleanup for derived classes
    // This guarantees that when a derived class is deleted through a BaseStrategy pointer,
    // its destructor is called correctly.
    virtual ~BaseStrategy() = default;

    // Method to execute the strategy
    // This pure virtual function forces derived classes to define their specific execution logic.
    // It is expected that this method will contain the core logic of the trading strategy.
    virtual void execute() = 0;

    // Optional: Method to configure the strategy with necessary parameters
    // This method allows the strategy to be configured dynamically using a configuration string.
    // Derived classes should implement how they parse and apply the configuration.
    virtual void configure(const std::string& config) = 0;

    // Optional: Analyze the results after the strategy has been executed
    // After the strategy has been run, this method can be used to analyze the results, 
    // such as calculating performance metrics. It returns a summary of the analysis as a string.
    virtual std::string analyzeResults() const = 0;
};

#endif // BASE_STRATEGY_H
