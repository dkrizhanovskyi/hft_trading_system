#ifndef COMMON_H
#define COMMON_H

#include <string>
#include <vector>

// Общие типы данных, используемые в проекте
using DataPoint = std::string;  // Пример типа данных

// Вспомогательные функции
inline std::string formatData(const std::string& data) {
    return "Formatted: " + data;
}

#endif // COMMON_H
