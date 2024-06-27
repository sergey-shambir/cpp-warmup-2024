cmake_minimum_required(VERSION 3.29)
project(aisd CXX)

find_package(Catch2 REQUIRED)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_executable(01_sqrt 01_sqrt/main.cpp)
target_link_libraries(01_sqrt Catch2::Catch2WithMain)
