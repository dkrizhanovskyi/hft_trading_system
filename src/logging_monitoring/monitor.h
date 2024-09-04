#ifndef MONITOR_H
#define MONITOR_H

#include <string>
#include <vector>
#include <utility>  // For std::pair

// The Monitor class is responsible for tracking system metrics.
// Metrics are stored as name-value pairs and can be reported for monitoring system performance.
class Monitor {
public:
    // Add a metric to the monitor.
    // Takes the name of the metric and its value and stores it for later reporting.
    void addMetric(const std::string& name, double value);

    // Report all stored metrics.
    // This method outputs all metrics and their values to the console.
    void reportMetrics() const;

private:
    // Store metrics as a vector of name-value pairs.
    // Each metric is represented by a string (name) and a double (value).
    std::vector<std::pair<std::string, double>> metrics_;
};

#endif // MONITOR_H
