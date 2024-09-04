// src/logging_monitoring/monitor.cpp

#include "monitor.h"
#include <iostream>  // For reporting metrics

void Monitor::addMetric(const std::string& name, double value) {
    metrics_.emplace_back(name, value);
}

void Monitor::reportMetrics() const {
    std::cout << "System Metrics:" << std::endl;
    for (const auto& metric : metrics_) {
        std::cout << metric.first << ": " << metric.second << std::endl;
    }
}
