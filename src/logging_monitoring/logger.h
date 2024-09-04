// src/logging_monitoring/logger.h

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

class Logger {
public:
    // Constructor takes the log file name
    Logger(const std::string& logFile);

    // Method to log a message
    void log(const std::string& message);

    // Destructor to close the file
    ~Logger();

private:
    std::ofstream logStream_;  // Output stream for logging
};

#endif // LOGGER_H
