#include <gtest/gtest.h>
#include "logger.h"
#include <fstream>

// Test to ensure that Logger can log messages to a file
TEST(LoggerTests, CanLogToFile) {
    // Create a logger that writes to "test_log.txt"
    Logger logger("test_log.txt");

    // Log a message to the file
    logger.log("Test message");

    // Open the log file to read the logged message
    std::ifstream logFile("test_log.txt");
    std::string line;
    std::getline(logFile, line);  // Read the first line from the file
    logFile.close();  // Close the file after reading

    // Verify that the message logged to the file is the expected one
    EXPECT_EQ(line, "Test message");
}
