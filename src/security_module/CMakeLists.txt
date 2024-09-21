# Specify the minimum required version of CMake.
cmake_minimum_required(VERSION 3.20)

# Add a static library for the security module.
add_library(security_module STATIC
    hash_utils.cpp
    key_manager.cpp
    security.cpp
)

# Set the C and C++ standards for the security module.
set_target_properties(security_module PROPERTIES
    C_STANDARD 11
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for security_module.
# This includes the public headers for the security module.
target_include_directories(security_module
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include/security_module
)

# Find and link the OpenSSL package for cryptographic operations.
find_package(OpenSSL REQUIRED)
target_link_libraries(security_module PUBLIC OpenSSL::SSL OpenSSL::Crypto)

# Optionally, enable strict warnings and compile optimizations (uncomment if needed).
# target_compile_options(security_module PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
