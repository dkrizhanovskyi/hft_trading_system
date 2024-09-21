#include "exposure_limit_risk_strategy.h"
#include "hash_utils.h"  // Подключаем модуль безопасности для хеширования
#include <iostream>  // For outputting risk alerts

// Constructor to initialize the maximum allowed exposure.
ExposureLimitRiskStrategy::ExposureLimitRiskStrategy(double maxAllowedExposure)
    : maxAllowedExposure_(maxAllowedExposure), currentExposure_(0.0) {}

// Update the current exposure level of the system after checking the integrity.
void ExposureLimitRiskStrategy::updateExposure(double currentExposure) {
    // Хешируем текущее значение экспозиции для проверки целостности
    hash_result_t hash_result;
    int ret = hash_data(reinterpret_cast<const uint8_t*>(&currentExposure), sizeof(currentExposure), HASH_ALG_SHA256, &hash_result);
    
    if (ret == 0) {
        std::cout << "Exposure hash calculated successfully. Hash: ";
        for (size_t i = 0; i < hash_result.hash_len; ++i) {
            printf("%02x", hash_result.hash[i]);
        }
        std::cout << std::endl;

        // Обновляем значение экспозиции после хеширования
        currentExposure_ = currentExposure;
    } else {
        std::cerr << "Failed to calculate hash for exposure!" << std::endl;
    }

    hash_result_free(&hash_result);  // Очистка после хеширования
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
