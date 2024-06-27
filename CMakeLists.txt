cmake_minimum_required(VERSION 3.29)
project(aisd CXX)

find_package(Catch2 3 REQUIRED)

# Enable C++20 globally
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# Expored commands used for VSCode C++ IntelliSense
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(01_sqrt 01_sqrt/main.cpp)
target_link_libraries(01_sqrt PRIVATE Catch2::Catch2WithMain)

add_executable(02_eratosthenes 02_eratosthenes/main.cpp)
target_link_libraries(02_eratosthenes PRIVATE Catch2::Catch2WithMain)

add_executable(03_hash_table 03_hash_table/hash_table.cpp 03_hash_table/hash_table_test.cpp)
target_link_libraries(03_hash_table PRIVATE Catch2::Catch2WithMain)
