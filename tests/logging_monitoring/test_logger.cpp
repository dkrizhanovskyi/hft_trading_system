#include <gtest/gtest.h>
#include "logger.h"
#include <fstream>

TEST(LoggerTests, CanLogToFile) {
    Logger logger("test_log.txt");
    logger.log("Test message");

    std::ifstream logFile("test_log.txt");
    std::string line;
    std::getline(logFile, line);
    logFile.close();

    EXPECT_EQ(line, "Test message");
}
