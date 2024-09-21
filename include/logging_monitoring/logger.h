#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>

// The Logger class is responsible for writing log messages to a file.
// It handles opening the log file, writing messages, and ensuring the file is properly closed.
class Logger {
public:
    // Constructor takes the log file name as a parameter and opens the file in append mode.
    Logger(const std::string& logFile);

    // Method to log a message to the file.
    // The message is appended to the log file with each call.
    void log(const std::string& message);

    // Destructor to ensure the log file is properly closed.
    ~Logger();

private:
    // Output stream for logging to a file.
    std::ofstream logStream_;
};

#endif // LOGGER_H
