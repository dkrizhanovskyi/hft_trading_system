#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>

namespace config {

// Путь к файлу с историческими данными
const std::string HISTORICAL_DATA_FILE = "data/historical_data.csv";

// Настройки стратегий
const int SCALPING_STRATEGY_THRESHOLD = 5;
const int MEAN_REVERSION_STRATEGY_PERIOD = 20;

// Другие параметры
const double MAX_DRAWDOWN_LIMIT = 0.2;  // 20%
const int MAX_EXPOSURE_LIMIT = 1000000;  // 1M units

} // namespace config

#endif // SETTINGS_H
