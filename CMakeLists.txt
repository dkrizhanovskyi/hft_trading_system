# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Define the project
project(HFTTradingSystem VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable strict compilation flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Add OpenSSL detection
find_package(OpenSSL REQUIRED)

# Add subdirectories for different modules
add_subdirectory(src/strategies)
add_subdirectory(src/data_processing)
add_subdirectory(src/order_execution)
add_subdirectory(src/risk_management)
add_subdirectory(src/logging_monitoring)
add_subdirectory(src/ui)
add_subdirectory(src/backtesting)
add_subdirectory(src/security_module)  # Add security_module subdirectory

# Add the main executable
add_executable(HFTTradingSystem src/main.cpp)

# Include directories for all modules
target_include_directories(HFTTradingSystem PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/backtesting
    ${CMAKE_SOURCE_DIR}/include/strategies
    ${CMAKE_SOURCE_DIR}/include/data_processing
    ${CMAKE_SOURCE_DIR}/include/order_execution
    ${CMAKE_SOURCE_DIR}/include/risk_management
    ${CMAKE_SOURCE_DIR}/include/logging_monitoring
    ${CMAKE_SOURCE_DIR}/include/ui
    ${CMAKE_SOURCE_DIR}/include/security_module  # Add security_module headers
)

# Link the necessary libraries
target_link_libraries(HFTTradingSystem
    strategies
    data_processing
    order_execution
    risk_management
    logging_monitoring
    ui
    backtesting
    security_module  # Link the security_module
    OpenSSL::Crypto  # Ensure OpenSSL is linked
    OpenSSL::SSL  # Link OpenSSL SSL after detection
)

# Enable testing
enable_testing()

# Add tests subdirectory
add_subdirectory(tests)

# Post-build command
add_custom_target(post_build
    COMMAND ${CMAKE_COMMAND} -E echo "Build complete for HFTTradingSystem"
)
