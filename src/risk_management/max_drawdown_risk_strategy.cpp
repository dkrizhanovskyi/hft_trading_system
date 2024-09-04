#include "max_drawdown_risk_strategy.h"
#include <iostream>  // For outputting risk alerts

// Constructor to initialize the maximum allowed drawdown.
MaxDrawdownRiskStrategy::MaxDrawdownRiskStrategy(double maxAllowedDrawdown)
    : maxAllowedDrawdown_(maxAllowedDrawdown), currentDrawdown_(0.0) {}

// Update the current drawdown level of the system.
void MaxDrawdownRiskStrategy::updateDrawdown(double currentDrawdown) {
    currentDrawdown_ = currentDrawdown;
}

// Evaluate the risk based on the current drawdown.
// If the current drawdown exceeds the allowed threshold, it prints an alert and returns `false`.
bool MaxDrawdownRiskStrategy::evaluateRisk() {
    if (currentDrawdown_ > maxAllowedDrawdown_) {
        std::cout << "Risk Alert: Maximum drawdown exceeded!" << std::endl;
        return false;  // Risk is too high
    }
    return true;  // Risk is acceptable
}
