# Specify the minimum required version of CMake
# This ensures that the project uses features from CMake version 3.20 or higher.
cmake_minimum_required(VERSION 3.20)

# Add a static library for the strategies module
# This library groups all strategy-related source files together into a single static library.
add_library(strategies STATIC
    base_strategy.cpp
    strategy_manager.cpp
    scalping_strategy.cpp
    mean_reversion_strategy.cpp
)

# Set C++ standard to C++20 for this module
# This ensures that the strategies module is compiled with the C++20 standard.
# It explicitly requires the standard and disables extensions for portability and consistency.
set_target_properties(strategies PROPERTIES
    CXX_STANDARD 20            # Use the C++20 standard
    CXX_STANDARD_REQUIRED ON    # Enforce the C++20 standard (don't fallback to older versions)
    CXX_EXTENSIONS OFF          # Disable compiler-specific extensions to ensure portability
)

# Include directories for strategies
# This makes the current source directory visible to files that include headers from the strategies module.
# This allows other modules to use the header files of strategies (e.g., base_strategy.h) without specifying paths.
target_include_directories(strategies
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}  # Include the current directory as a public include path
)

# Link any additional libraries if needed (currently commented out).
# If this module depends on other external libraries, they can be linked here.
# For example, you might link a library for data processing or networking.
# target_link_libraries(strategies PUBLIC some_external_library)

# Enable strict warnings and compile optimizations (commented out).
# These compile options are useful for catching potential issues early by treating all warnings as errors (-Werror).
# You can enable them during development to ensure high code quality.
# target_compile_options(strategies PRIVATE
#     -Wall -Wextra -pedantic -Werror   # Enable warnings and treat warnings as errors
# )
