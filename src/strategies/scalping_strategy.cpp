#include "scalping_strategy.h"
#include <atomic>    // Для атомарного счетчика в многопоточной среде

// Атомарный счетчик для многопоточной среды
std::atomic<int> tradesExecuted_{0};

// Configures the scalping strategy with necessary parameters.
// Future implementation where config will contain real settings.
void ScalpingStrategy::configure([[maybe_unused]] const std::string& config) {
    // Parsing and applying configuration will be added here.
}

// Executes the scalping strategy.
// Now uses atomic increment for trade execution to ensure thread safety.
void ScalpingStrategy::execute() {
    // Increment the trade counter atomically
    tradesExecuted_++;
    std::cout << "Scalping trade executed! Total trades: " << tradesExecuted_.load() << std::endl;
}

// Analyzes the results of the scalping strategy.
// Uses atomic load to safely retrieve the trade counter.
std::string ScalpingStrategy::analyzeResults() const {
    return "Scalping strategy executed " + std::to_string(tradesExecuted_.load()) + " trades.";
}
