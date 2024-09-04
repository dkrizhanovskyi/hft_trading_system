# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.20)

# Add a library for the strategies module
add_library(strategies STATIC
    base_strategy.cpp
    strategy_manager.cpp
    scalping_strategy.cpp
    mean_reversion_strategy.cpp
)

# Set C++ standard to C++20 for this module
set_target_properties(strategies PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for strategies
target_include_directories(strategies
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link any additional libraries if needed (remove if not necessary)
# target_link_libraries(strategies PUBLIC some_external_library)

# Enable strict warnings and compile optimizations
#target_compile_options(data_processing PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
