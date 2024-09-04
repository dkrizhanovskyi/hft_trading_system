// src/strategies/scalping_strategy.h

#ifndef SCALPING_STRATEGY_H
#define SCALPING_STRATEGY_H

#include "base_strategy.h"
#include <iostream>
#include <string>

class ScalpingStrategy : public BaseStrategy {
public:
    // Configure the scalping strategy with necessary parameters
    void configure(const std::string& config) override;

    // Execute the scalping strategy
    void execute() override;

    // Analyze the results of the scalping strategy
    std::string analyzeResults() const override;

private:
    double threshold_ = 0.01;  // Example threshold for triggering trades
    int tradesExecuted_ = 0;
};

#endif // SCALPING_STRATEGY_H
