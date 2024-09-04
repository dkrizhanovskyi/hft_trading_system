#ifndef SCALPING_STRATEGY_H
#define SCALPING_STRATEGY_H

#include "base_strategy.h"
#include <iostream>
#include <string>

// ScalpingStrategy is a derived class from BaseStrategy.
// This class implements a simple scalping strategy where trades are triggered
// based on a predefined threshold. It provides methods to configure, execute, and analyze the strategy.
class ScalpingStrategy : public BaseStrategy {
public:
    // Configure the scalping strategy with necessary parameters.
    // This method allows the strategy to be configured via a string (e.g., JSON or CSV format).
    // For now, this is a placeholder and can be extended to parse and apply actual configuration settings.
    void configure(const std::string& config) override;

    // Execute the scalping strategy.
    // This method contains the core logic for the scalping strategy. In this example, it simply increments
    // the number of executed trades, but in a real-world scenario, it would analyze market data
    // and execute trades based on predefined rules.
    void execute() override;

    // Analyze the results of the scalping strategy.
    // This method provides a summary of the trades executed by the scalping strategy,
    // returning a string that describes the results.
    std::string analyzeResults() const override;

private:
    // Example threshold for triggering trades.
    // This value would normally be used in the logic that decides whether a trade should be executed.
    double threshold_ = 0.01;

    // Counter for the number of trades executed.
    int tradesExecuted_ = 0;
};

#endif // SCALPING_STRATEGY_H
