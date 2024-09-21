# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a static library for the backtesting module
# This library includes the backtester and historical data loader components.
add_library(backtesting STATIC
    backtester.cpp
    historical_data_loader.cpp
)

# Set the C++ standard to C++20
# Ensures the code is compiled with C++20 standard.
set_target_properties(backtesting PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for strategies and data processing modules
# Use the new include directory paths
target_include_directories(backtesting PUBLIC 
    ${CMAKE_SOURCE_DIR}/include/strategies
    ${CMAKE_SOURCE_DIR}/include/data_processing
    ${CMAKE_SOURCE_DIR}/include/backtesting
)

# Link the strategies and data processing libraries
target_link_libraries(backtesting PUBLIC strategies data_processing)

# Link external libraries if necessary (none for now)
# target_link_libraries(backtesting PUBLIC some_library)

# Enable strict warnings and compile optimizations (optional, currently commented out)
# target_compile_options(backtesting PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
