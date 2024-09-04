#include "monitor.h"
#include <iostream>  // For reporting metrics to the console

// Add a metric to the monitor by storing its name and value in the vector.
void Monitor::addMetric(const std::string& name, double value) {
    metrics_.emplace_back(name, value);
}

// Report all stored metrics by iterating over the vector and printing each name-value pair.
void Monitor::reportMetrics() const {
    std::cout << "System Metrics:" << std::endl;
    for (const auto& metric : metrics_) {
        std::cout << metric.first << ": " << metric.second << std::endl;
    }
}
