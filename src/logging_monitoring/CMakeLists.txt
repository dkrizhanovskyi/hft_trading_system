# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a library for the logging and monitoring module
add_library(logging_monitoring STATIC
    logger.cpp
    monitor.cpp
)

# Set the C++ standard to C++20
set_target_properties(logging_monitoring PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for logging and monitoring
target_include_directories(logging_monitoring
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link external libraries if necessary (none for now)
# target_link_libraries(logging_monitoring PUBLIC some_library)

# Enable strict warnings and compile optimizations
#target_compile_options(data_processing PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
