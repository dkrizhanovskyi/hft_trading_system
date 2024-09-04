// src/strategies/mean_reversion_strategy.h

#ifndef MEAN_REVERSION_STRATEGY_H
#define MEAN_REVERSION_STRATEGY_H

#include "base_strategy.h"
#include <iostream>
#include <string>

class MeanReversionStrategy : public BaseStrategy {
public:
    // Configure the mean reversion strategy
    void configure(const std::string& config) override;

    // Execute the mean reversion strategy
    void execute() override;

    // Analyze the results of the mean reversion strategy
    std::string analyzeResults() const override;

private:
    double meanPrice_ = 100.0;  // Example mean price
    int tradesExecuted_ = 0;
};

#endif // MEAN_REVERSION_STRATEGY_H
