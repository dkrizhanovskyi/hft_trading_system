#include "exposure_limit_risk_strategy.h"
#include <iostream>  // For outputting risk alerts

// Constructor to initialize the maximum allowed exposure.
ExposureLimitRiskStrategy::ExposureLimitRiskStrategy(double maxAllowedExposure)
    : maxAllowedExposure_(maxAllowedExposure), currentExposure_(0.0) {}

// Update the current exposure level of the system.
void ExposureLimitRiskStrategy::updateExposure(double currentExposure) {
    currentExposure_ = currentExposure;
}

// Evaluate the risk based on the current exposure.
// If the current exposure exceeds the allowed threshold, it prints an alert and returns `false`.
bool ExposureLimitRiskStrategy::evaluateRisk() {
    if (currentExposure_ > maxAllowedExposure_) {
        std::cout << "Risk Alert: Exposure limit exceeded!" << std::endl;
        return false;  // Risk is too high
    }
    return true;  // Risk is acceptable
}
