# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.20)

# Add a static library for the order execution module
# This library includes both the order executor and the exchange connector.
add_library(order_execution STATIC
    exchange_connector.cpp
    order_executor.cpp
)

# Set the C++ standard to C++20
# Ensures the code is compiled with the C++20 standard and disables compiler-specific extensions.
set_target_properties(order_execution PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for order execution
# This allows other modules to include the headers from this library.
target_include_directories(order_execution
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/include/security_module
        ${CMAKE_SOURCE_DIR}/include/order_execution
)

# Link the security module with order execution.
target_link_libraries(order_execution
    PUBLIC
        security_module  # Link security_module to provide cryptographic functions
)