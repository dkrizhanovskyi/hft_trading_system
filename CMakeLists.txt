# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Define the project
project(HFTTradingSystem VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable strict compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -pg")

# Add subdirectories for different modules
add_subdirectory(src/strategies)
add_subdirectory(src/data_processing)
add_subdirectory(src/order_execution)
add_subdirectory(src/risk_management)
add_subdirectory(src/logging_monitoring)
add_subdirectory(src/ui)
add_subdirectory(src/backtesting)

# Add the main executable
add_executable(HFTTradingSystem src/main.cpp)

# Link the necessary libraries
target_link_libraries(HFTTradingSystem
    strategies
    data_processing
    order_execution
    risk_management
    logging_monitoring
    ui
    backtesting
)

# Set the include directories
target_include_directories(HFTTradingSystem PUBLIC
    src/backtesting
    src/strategies
    src/data_processing
    src/order_execution
    src/risk_management
    src/logging_monitoring
    src/ui
)

# Add tests subdirectory
add_subdirectory(tests)
