// src/logging_monitoring/logger.cpp

#include "logger.h"
#include <iostream>  // For console output (optional)

Logger::Logger(const std::string& logFile)
    : logStream_(logFile, std::ios::app) {  // Open the log file in append mode
    if (!logStream_) {
        throw std::runtime_error("Unable to open log file: " + logFile);
    }
    std::cout << "Logging to file: " << logFile << std::endl;  // Optional console output
}

void Logger::log(const std::string& message) {
    logStream_ << message << std::endl;
}

Logger::~Logger() {
    if (logStream_.is_open()) {
        logStream_.close();  // Ensure the log file is closed
    }
}
