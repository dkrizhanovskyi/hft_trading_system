# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a static library for the UI module
# This library includes the UIManager component for handling user interactions.
add_library(ui STATIC
    ui_manager.cpp
)

# Set the C++ standard to C++20
# Ensures the code is compiled using C++20 features.
set_target_properties(ui PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for the UI module
# This allows other modules to include the headers from this library.
target_include_directories(ui
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include/ui
)

# Link external libraries if necessary (currently commented out)
# target_link_libraries(ui PUBLIC some_library)

# Enable strict warnings and compile optimizations (optional, currently commented out)
# target_compile_options(ui PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
