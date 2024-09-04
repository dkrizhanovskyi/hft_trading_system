# Enable testing support
enable_testing()

# Include GoogleTest using FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add GoogleTest framework and link the necessary libraries
add_executable(test_backtester backtesting/test_backtester.cpp)
target_include_directories(test_backtester PUBLIC ${CMAKE_SOURCE_DIR}/src/backtesting)
target_link_libraries(test_backtester gtest gtest_main backtesting data_processing strategies)

add_executable(test_data_processor data_processing/test_data_processor.cpp)
target_include_directories(test_data_processor PUBLIC ${CMAKE_SOURCE_DIR}/src/data_processing)
target_link_libraries(test_data_processor gtest gtest_main data_processing)

add_executable(test_logger logging_monitoring/test_logger.cpp)
target_include_directories(test_logger PUBLIC ${CMAKE_SOURCE_DIR}/src/logging_monitoring)
target_link_libraries(test_logger gtest gtest_main logging_monitoring)

add_executable(test_order_executor order_execution/test_order_executor.cpp)
target_include_directories(test_order_executor PUBLIC ${CMAKE_SOURCE_DIR}/src/order_execution)
target_link_libraries(test_order_executor gtest gtest_main order_execution)

add_executable(test_risk_manager risk_management/test_risk_manager.cpp)
target_include_directories(test_risk_manager PUBLIC ${CMAKE_SOURCE_DIR}/src/risk_management)
target_link_libraries(test_risk_manager gtest gtest_main risk_management)

add_executable(test_scalping_strategy strategies/test_scalping_strategy.cpp)
target_include_directories(test_scalping_strategy PUBLIC ${CMAKE_SOURCE_DIR}/src/strategies)
target_link_libraries(test_scalping_strategy gtest gtest_main strategies)

add_executable(test_ui_manager ui/test_ui_manager.cpp)
target_include_directories(test_ui_manager PUBLIC ${CMAKE_SOURCE_DIR}/src/ui)
target_link_libraries(test_ui_manager gtest gtest_main ui)

# Register tests
add_test(NAME BacktesterTests COMMAND test_backtester)
add_test(NAME DataProcessorTests COMMAND test_data_processor)
add_test(NAME LoggerTests COMMAND test_logger)
add_test(NAME OrderExecutorTests COMMAND test_order_executor)
add_test(NAME RiskManagerTests COMMAND test_risk_manager)
add_test(NAME ScalpingStrategyTests COMMAND test_scalping_strategy)
add_test(NAME UIManagerTests COMMAND test_ui_manager)
