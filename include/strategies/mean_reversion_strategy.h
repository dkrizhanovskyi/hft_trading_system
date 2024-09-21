#ifndef MEAN_REVERSION_STRATEGY_H
#define MEAN_REVERSION_STRATEGY_H

#include "base_strategy.h"
#include <iostream>
#include <string>

// MeanReversionStrategy is a derived class from BaseStrategy.
// This class implements a simple mean reversion trading strategy, where trades are executed
// based on a reversion to a mean price level. It provides methods to configure, execute, and analyze the strategy.
class MeanReversionStrategy : public BaseStrategy {
public:
    // Configure the mean reversion strategy with necessary parameters.
    // This method is used to apply configuration settings like the mean price and other parameters
    // that influence the strategy's behavior. For now, it serves as a placeholder.
    void configure(const std::string& config) override;

    // Execute the mean reversion strategy.
    // This method contains the core logic for executing the mean reversion strategy. In this simplified
    // version, it simply increments the number of trades executed, but in a full implementation,
    // it would involve analyzing price data and making trade decisions based on the difference from the mean price.
    void execute() override;

    // Analyze the results of the mean reversion strategy.
    // After the strategy has been run, this method provides a summary of the number of trades executed.
    std::string analyzeResults() const override;

private:
    // Example mean price for the mean reversion strategy.
    // This value represents the price level around which the strategy expects prices to revert.
    double meanPrice_ = 100.0;

    // Counter for the number of trades executed.
    int tradesExecuted_ = 0;
};

#endif // MEAN_REVERSION_STRATEGY_H
