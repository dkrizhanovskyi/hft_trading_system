#include "exposure_limit_risk_strategy.h"
#include <iostream>  // Добавляем этот заголовочный файл

ExposureLimitRiskStrategy::ExposureLimitRiskStrategy(double maxAllowedExposure)
    : maxAllowedExposure_(maxAllowedExposure), currentExposure_(0.0) {}

void ExposureLimitRiskStrategy::updateExposure(double currentExposure) {
    currentExposure_ = currentExposure;
}

bool ExposureLimitRiskStrategy::evaluateRisk() {
    if (currentExposure_ > maxAllowedExposure_) {
        std::cout << "Risk Alert: Exposure limit exceeded!" << std::endl;  // Исправлено
        return false;  // Risk is too high
    }
    return true;  // Risk is acceptable
}
