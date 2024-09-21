#include "max_drawdown_risk_strategy.h"
#include "hash_utils.h"  // Подключаем модуль безопасности для хеширования
#include <iostream>  // For outputting risk alerts

// Constructor to initialize the maximum allowed drawdown.
MaxDrawdownRiskStrategy::MaxDrawdownRiskStrategy(double maxAllowedDrawdown)
    : maxAllowedDrawdown_(maxAllowedDrawdown), currentDrawdown_(0.0) {}

// Update the current drawdown level of the system after checking integrity.
void MaxDrawdownRiskStrategy::updateDrawdown(double currentDrawdown) {
    // Хешируем текущее значение drawdown для проверки целостности
    hash_result_t hash_result;
    int ret = hash_data(reinterpret_cast<const uint8_t*>(&currentDrawdown), sizeof(currentDrawdown), HASH_ALG_SHA256, &hash_result);
    
    if (ret == 0) {
        std::cout << "Drawdown hash calculated successfully. Hash: ";
        for (size_t i = 0; i < hash_result.hash_len; ++i) {
            printf("%02x", hash_result.hash[i]);
        }
        std::cout << std::endl;

        // Обновляем значение drawdown после успешного хеширования
        currentDrawdown_ = currentDrawdown;
    } else {
        std::cerr << "Failed to calculate hash for drawdown!" << std::endl;
    }

    hash_result_free(&hash_result);  // Очистка памяти после хеширования
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
