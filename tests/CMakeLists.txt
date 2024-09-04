# Указываем минимально необходимую версию CMake
cmake_minimum_required(VERSION 3.20)

# Подключаем GoogleTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Включаем поддержку тестов
enable_testing()

# Тесты для модуля backtesting
add_executable(backtesting_tests
    backtesting/test_backtester.cpp
)
# Добавляем директории с заголовками для backtesting
target_include_directories(backtesting_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/backtesting)
# Линкуем библиотеку backtesting и GoogleTest
target_link_libraries(backtesting_tests PRIVATE backtesting GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME BacktestingTests COMMAND backtesting_tests)

# Тесты для модуля data_processing
add_executable(data_processing_tests
    data_processing/test_data_processor.cpp
)
# Добавляем директории с заголовками для data_processing
target_include_directories(data_processing_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/data_processing)
# Линкуем библиотеку data_processing и GoogleTest
target_link_libraries(data_processing_tests PRIVATE data_processing GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME DataProcessingTests COMMAND data_processing_tests)

# Тесты для модуля strategies
add_executable(strategies_tests
    strategies/test_scalping_strategy.cpp
)
# Добавляем директории с заголовками для strategies
target_include_directories(strategies_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/strategies)
# Линкуем библиотеку strategies и GoogleTest
target_link_libraries(strategies_tests PRIVATE strategies GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME StrategiesTests COMMAND strategies_tests)

# Тесты для модуля order_execution
add_executable(order_execution_tests
    order_execution/test_order_executor.cpp
)
# Добавляем директории с заголовками для order_execution
target_include_directories(order_execution_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/order_execution)
# Линкуем библиотеку order_execution и GoogleTest
target_link_libraries(order_execution_tests PRIVATE order_execution GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME OrderExecutionTests COMMAND order_execution_tests)

# Тесты для модуля risk_management
add_executable(risk_management_tests
    risk_management/test_risk_manager.cpp
)
# Добавляем директории с заголовками для risk_management
target_include_directories(risk_management_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/risk_management)
# Линкуем библиотеку risk_management и GoogleTest
target_link_libraries(risk_management_tests PRIVATE risk_management GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME RiskManagementTests COMMAND risk_management_tests)

# Тесты для модуля logging_monitoring
add_executable(logging_monitoring_tests
    logging_monitoring/test_logger.cpp
)
# Добавляем директории с заголовками для logging_monitoring
target_include_directories(logging_monitoring_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/logging_monitoring)
# Линкуем библиотеку logging_monitoring и GoogleTest
target_link_libraries(logging_monitoring_tests PRIVATE logging_monitoring GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME LoggingMonitoringTests COMMAND logging_monitoring_tests)

# Тесты для модуля ui
add_executable(ui_tests
    ui/test_ui_manager.cpp
)
# Добавляем директории с заголовками для ui
target_include_directories(ui_tests PRIVATE ${CMAKE_SOURCE_DIR}/src/ui)
# Линкуем библиотеку ui и GoogleTest
target_link_libraries(ui_tests PRIVATE ui GTest::gtest GTest::gtest_main)
# Регистрируем тесты
add_test(NAME UITests COMMAND ui_tests)

# Убедитесь, что все модули и тесты добавлены корректно.
