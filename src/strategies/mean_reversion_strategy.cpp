#include "mean_reversion_strategy.h"

// Configures the mean reversion strategy with necessary parameters.
// In a real implementation, the config string could be used to dynamically set the mean price
// and other parameters relevant to the strategy. Currently, it just prints the initial mean price.
void MeanReversionStrategy::configure(const std::string& config) {
    // Logic for parsing and applying configuration would go here.
    std::cout << "Mean reversion strategy configured with mean price: " << meanPrice_ << std::endl;
}

// Executes the mean reversion strategy.
// In this example, it simply simulates a trade execution by incrementing the trade counter.
// In a real-world scenario, this method would involve checking market data and executing trades
// when prices deviate from the mean price.
void MeanReversionStrategy::execute() {
    tradesExecuted_++;
    std::cout << "Mean reversion trade executed! Total trades: " << tradesExecuted_ << std::endl;
}

// Analyzes the results of the mean reversion strategy.
// This method returns a summary of the trades executed, including the total number of trades performed by the strategy.
std::string MeanReversionStrategy::analyzeResults() const {
    return "Mean reversion strategy executed " + std::to_string(tradesExecuted_) + " trades.";
}
