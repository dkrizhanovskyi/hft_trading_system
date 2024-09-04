# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a library for the data processing module
add_library(data_processing STATIC
    data_collector.cpp
    data_processor.cpp
)

# Set the C++ standard to C++20
set_target_properties(data_processing PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for data processing
target_include_directories(data_processing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link external libraries if necessary (none for now)
# target_link_libraries(data_processing PUBLIC some_library)

# Enable strict warnings and compile optimizations
#target_compile_options(data_processing PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
