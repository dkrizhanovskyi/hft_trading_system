# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a library for the UI module
add_library(ui STATIC
    ui_manager.cpp
)

# Set the C++ standard to C++20
set_target_properties(ui PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for the UI module
target_include_directories(ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link external libraries if necessary (none for now)
# target_link_libraries(ui PUBLIC some_library)

# Enable strict warnings and compile optimizations
#target_compile_options(data_processing PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
