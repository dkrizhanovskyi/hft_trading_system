# Specify the minimum required version of CMake.
cmake_minimum_required(VERSION 3.20)

# Add a static library for the data processing module.
add_library(data_processing STATIC
    data_collector.cpp
    data_processor.cpp
)

# Set the C++ standard to C++20 for the data processing module.
set_target_properties(data_processing PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

# Include directories for data processing.
# This includes the headers of the data processing library and security module.
target_include_directories(data_processing
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}                    # Для include файлов модуля data_processing
        ${CMAKE_SOURCE_DIR}/include/data_processing    # Новый путь для заголовков в include
        ${CMAKE_SOURCE_DIR}/include/security_module    # Путь к security_module
)

# Link the security_module library with data_processing.
target_link_libraries(data_processing
    PUBLIC
        security_module  # Линкуем модуль безопасности
)

# Optionally, enable strict warnings and compile optimizations.
# Uncomment to enable these flags during development.
# target_compile_options(data_processing PRIVATE
#     -Wall -Wextra -pedantic -Werror
# )
