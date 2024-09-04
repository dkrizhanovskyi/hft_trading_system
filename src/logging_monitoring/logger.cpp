#include "logger.h"
#include <iostream>  // Optional: For console output to indicate the logging status

// Constructor that opens the log file in append mode.
// Throws a runtime error if the file cannot be opened.
Logger::Logger(const std::string& logFile)
    : logStream_(logFile, std::ios::app) {  // Open the log file in append mode
    if (!logStream_) {
        throw std::runtime_error("Unable to open log file: " + logFile);
    }
    std::cout << "Logging to file: " << logFile << std::endl;  // Optional console output
}

// Log a message by appending it to the log file.
void Logger::log(const std::string& message) {
    logStream_ << message << std::endl;
}

// Destructor to ensure the log file is properly closed when the Logger object is destroyed.
Logger::~Logger() {
    if (logStream_.is_open()) {
        logStream_.close();
    }
}
