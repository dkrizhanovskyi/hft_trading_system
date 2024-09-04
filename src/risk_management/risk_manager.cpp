#include "risk_manager.h"
#include <future>  // Для асинхронного выполнения

// Adds a risk strategy to the list of strategies managed by the RiskManager.
void RiskManager::addRiskStrategy(std::shared_ptr<RiskStrategy> strategy) {
    riskStrategies_.emplace_back(strategy);
}

// Evaluates all risk strategies asynchronously.
// If any strategy reports that the risk is too high (returns false), the method will return false.
// Otherwise, it returns true. Each strategy is evaluated concurrently to speed up the process.
bool RiskManager::assessRisk() {
    std::vector<std::future<bool>> futures;
    
    // Оценка стратегий в асинхронных задачах
    for (const auto& strategy : riskStrategies_) {
        futures.push_back(std::async(std::launch::async, [strategy]() {
            return strategy->evaluateRisk();
        }));
    }

    // Ждём завершения всех стратегий и проверяем результаты
    for (auto& future : futures) {
        if (!future.get()) {
            return false;  // Если хотя бы одна стратегия сигнализирует высокий риск
        }
    }

    return true;  // Все стратегии прошли успешно
}

// Clears the list of risk strategies, effectively resetting the manager.
void RiskManager::clearRiskStrategies() {
    riskStrategies_.clear();
}
