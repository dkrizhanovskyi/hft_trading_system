# Specify the minimum required version of CMake.
# This ensures the project uses features from CMake version 3.20 or higher.
cmake_minimum_required(VERSION 3.20)

# Add a static library for the data processing module.
# This library contains the data collection and processing components.
add_library(data_processing STATIC
    data_collector.cpp
    data_processor.cpp
)

# Set the C++ standard to C++20 for the data processing module.
# This guarantees the code is compiled with modern C++20 features.
set_target_properties(data_processing PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for data processing.
# This allows other modules to include the headers of the data processing library.
target_include_directories(data_processing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link external libraries if necessary (currently commented out).
# This section can be used to link additional dependencies or external libraries.
# target_link_libraries(data_processing PUBLIC some_library)

# Enable strict warnings and compile optimizations (commented out for now).
# This is useful during development to catch issues early by enabling extra warnings and treating them as errors.
# target_compile_options(data_processing PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
