# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a static library for the logging and monitoring module
# This library includes both the Logger and Monitor components.
add_library(logging_monitoring STATIC
    logger.cpp
    monitor.cpp
)

# Set the C++ standard to C++20
# This ensures the code is compiled using the C++20 standard.
set_target_properties(logging_monitoring PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for logging and monitoring
# This allows other modules to include the headers from this library.
target_include_directories(logging_monitoring
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}                    # Включаем текущую директорию
        ${CMAKE_SOURCE_DIR}/include/logging_monitoring # Включаем заголовочные файлы в include/logging_monitoring
)

# Link external libraries if necessary (currently commented out)
# target_link_libraries(logging_monitoring PUBLIC some_library)

# Enable strict warnings and compile optimizations (optional, currently commented out)
# Uncomment to enable these flags during development.
# target_compile_options(logging_monitoring PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
