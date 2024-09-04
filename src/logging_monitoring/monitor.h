// src/logging_monitoring/monitor.h

#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>
#include <utility>  // For std::pair

class Monitor {
public:
    // Add a metric to the monitor
    void addMetric(const std::string& name, double value);

    // Report all metrics
    void reportMetrics() const;

private:
    // Store metrics as name-value pairs
    std::vector<std::pair<std::string, double>> metrics_;
};

#endif // MONITOR_H
