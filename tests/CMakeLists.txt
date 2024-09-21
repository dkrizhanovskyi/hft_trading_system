# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable for backtesting
add_executable(test_backtester
    backtesting/test_backtester.cpp
)
target_link_libraries(test_backtester
    backtesting  # Link with backtesting library
    strategies
    data_processing
    order_execution
    risk_management
    logging_monitoring
    security_module  # Link security_module for tests
    GTest::GTest  # Link Google Test
    GTest::Main   # Link Google Test main
    pthread       # Link pthread, required by GTest
)

# Add test executable for data processing
add_executable(test_data_processor
    data_processing/test_data_processor.cpp
)
target_link_libraries(test_data_processor
    data_processing  # Link with data_processing library
    security_module  # Link security_module if needed for encryption
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for logging and monitoring
add_executable(test_logger
    logging_monitoring/test_logger.cpp
)
target_link_libraries(test_logger
    logging_monitoring  # Link with logging_monitoring library
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for order execution
add_executable(test_order_executor
    order_execution/test_order_executor.cpp
)
target_link_libraries(test_order_executor
    order_execution  # Link with order_execution library
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for risk management
add_executable(test_risk_manager
    risk_management/test_risk_manager.cpp
)
target_link_libraries(test_risk_manager
    risk_management  # Link with risk_management library
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for strategies
add_executable(test_scalping_strategy
    strategies/test_scalping_strategy.cpp
)
target_link_libraries(test_scalping_strategy
    strategies  # Link with strategies library
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for UI manager
add_executable(test_ui_manager
    ui/test_ui_manager.cpp
)
target_link_libraries(test_ui_manager
    ui  # Link with UI library
    GTest::GTest
    GTest::Main
    pthread
)

# Add test executable for security module tests
add_executable(test_hash_utils
    security_module/test_hash_utils.cpp
)
target_link_libraries(test_hash_utils
    security_module  # Link with security_module library
    GTest::GTest
    GTest::Main
    pthread
)

add_executable(test_key_manager
    security_module/test_key_manager.cpp
)
target_link_libraries(test_key_manager
    security_module  # Link with security_module library
    GTest::GTest
    GTest::Main
    pthread
)

add_executable(test_security
    security_module/test_security.cpp
)
target_link_libraries(test_security
    security_module  # Link with security_module library
    GTest::GTest
    GTest::Main
    pthread
)

# Enable testing with CTest
enable_testing()

# Add CTest commands for each test executable
add_test(NAME BacktesterTest COMMAND test_backtester)
add_test(NAME DataProcessorTest COMMAND test_data_processor)
add_test(NAME LoggerTest COMMAND test_logger)
add_test(NAME OrderExecutorTest COMMAND test_order_executor)
add_test(NAME RiskManagerTest COMMAND test_risk_manager)
add_test(NAME ScalpingStrategyTest COMMAND test_scalping_strategy)
add_test(NAME UIManagerTest COMMAND test_ui_manager)
add_test(NAME HashUtilsTest COMMAND test_hash_utils)
add_test(NAME KeyManagerTest COMMAND test_key_manager)
add_test(NAME SecurityTest COMMAND test_security)
