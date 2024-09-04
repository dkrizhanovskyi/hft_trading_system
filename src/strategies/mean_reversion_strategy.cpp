// src/strategies/mean_reversion_strategy.cpp

#include "mean_reversion_strategy.h"

void MeanReversionStrategy::configure(const std::string& config) {
    // In a real implementation, this config could set the mean price and other parameters
    std::cout << "Mean reversion strategy configured with mean price: " << meanPrice_ << std::endl;
}

void MeanReversionStrategy::execute() {
    // Example logic for mean reversion, typically you'd check market data here
    tradesExecuted_++;
    std::cout << "Mean reversion trade executed! Total trades: " << tradesExecuted_ << std::endl;
}

std::string MeanReversionStrategy::analyzeResults() const {
    return "Mean reversion strategy executed " + std::to_string(tradesExecuted_) + " trades.";
}
