# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a library for the backtesting module
add_library(backtesting STATIC
    backtester.cpp
    historical_data_loader.cpp
)

# Set the C++ standard to C++20
set_target_properties(backtesting PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_include_directories(backtesting PUBLIC ../strategies ../data_processing)

target_link_libraries(backtesting PUBLIC strategies data_processing)

# Link external libraries if necessary (none for now)
# target_link_libraries(backtesting PUBLIC some_library)

# Enable strict warnings and compile optimizations
#target_compile_options(backtesting PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
