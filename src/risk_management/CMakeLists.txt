# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a library for the risk management module
add_library(risk_management STATIC
    risk_manager.cpp
    risk_strategy.cpp
    max_drawdown_risk_strategy.cpp
    exposure_limit_risk_strategy.cpp
)

# Set the C++ standard for this module
set_target_properties(risk_management PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for risk management
target_include_directories(risk_management
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link additional external libraries here if required (commented out for now)
# target_link_libraries(risk_management PUBLIC some_external_library)

# Enable strict warnings and compile optimizations
#target_compile_options(data_processing PRIVATE
#    -Wall -Wextra -pedantic -Werror
#)
