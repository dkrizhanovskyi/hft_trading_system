#include "max_drawdown_risk_strategy.h"
#include <iostream>  // Добавляем этот заголовочный файл

MaxDrawdownRiskStrategy::MaxDrawdownRiskStrategy(double maxAllowedDrawdown)
    : maxAllowedDrawdown_(maxAllowedDrawdown), currentDrawdown_(0.0) {}

void MaxDrawdownRiskStrategy::updateDrawdown(double currentDrawdown) {
    currentDrawdown_ = currentDrawdown;
}

bool MaxDrawdownRiskStrategy::evaluateRisk() {
    if (currentDrawdown_ > maxAllowedDrawdown_) {
        std::cout << "Risk Alert: Maximum drawdown exceeded!" << std::endl;  // Исправлено
        return false;  // Risk is too high
    }
    return true;  // Risk is acceptable
}
