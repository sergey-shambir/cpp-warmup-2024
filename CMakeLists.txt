cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(cpp-warmup-2024 CXX)

find_package(Catch2 3 REQUIRED)

enable_testing()

include(cmake/functions.cmake)

# Включаем C++20 во всём проекте
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Экспортируем команды для использования с VSCode C++ IntelliSense
# См. https://stackoverflow.com/questions/54671883/how-can-i-set-up-c-c-intellisense-for-a-cmake-project-in-vs-code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(01_sqrt)
add_subdirectory(02_eratosthenes)
add_subdirectory(03_hash_table)
add_subdirectory(04_flat_map)
add_subdirectory(05_avl_tree_map)
add_subdirectory(06_sparse_graph)
add_subdirectory(07_dinning_philosophers)
add_subdirectory(08_deep_first_search)
add_subdirectory(09_ant_visits)
add_subdirectory(10_max_subarray)
