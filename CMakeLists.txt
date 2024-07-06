cmake_minimum_required(VERSION 3.29 FATAL_ERROR)

project(cpp-warmup-2024 CXX)

find_package(Catch2 3 REQUIRED)

enable_testing()

# Регистрирует статическую библиотеку
function(custom_add_library_from_dir TARGET)
    # Собираем файлы с текущего каталога
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    list(FILTER TARGET_SRC EXCLUDE REGEX ".*_test\\.cpp$")
    add_library(${TARGET} ${TARGET_SRC})
endfunction()

# Регистрирует тесты, использующие Catch2 для запуска
function(custom_add_test_from_dir TEST_TARGET LIBRARY_UNDER_TEST)
    # Собираем файлы тестов с текущего каталога
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_executable(${TEST_TARGET} ${TARGET_SRC})
    # Добавляем компоновку с проверяемой библиотекой и Catch2
    target_link_libraries(${TEST_TARGET} PRIVATE ${LIBRARY_UNDER_TEST} Catch2::Catch2WithMain)
    # Регистрируем исполняемый файл в CMake как набор тестов.
    add_test(${TEST_TARGET} ${TEST_TARGET})
endfunction()

# Включаем C++20 во всём проекте
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Экспортируем команды для использования с VSCode C++ IntelliSense
# См. https://stackoverflow.com/questions/54671883/how-can-i-set-up-c-c-intellisense-for-a-cmake-project-in-vs-code
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(01_sqrt)
add_subdirectory(02_eratosthenes)

add_executable(03_hash_table 03_hash_table/hash_table.cpp 03_hash_table/hash_table_test.cpp)
target_link_libraries(03_hash_table PRIVATE Catch2::Catch2WithMain)

file(GLOB FLAT_MAP_FILES 04_flat_map/*.cpp)
add_executable(04_flat_map ${FLAT_MAP_FILES})
target_link_libraries(04_flat_map PRIVATE Catch2::Catch2WithMain)

file(GLOB AVL_TREE_FILES 05_avl_tree_map/*.cpp)
add_executable(05_avl_tree_map ${AVL_TREE_FILES})
target_link_libraries(05_avl_tree_map PRIVATE Catch2::Catch2WithMain)

file(GLOB SPARSE_GRAPH_FILES 06_sparce_graph/*.cpp)
add_executable(06_sparce_graph ${SPARSE_GRAPH_FILES})
target_link_libraries(06_sparce_graph PRIVATE Catch2::Catch2WithMain)

file(GLOB DINNIN_PHILOSOPHERS_FILES 07_dinning_philosophers/*.cpp)
add_executable(07_dinning_philosophers ${DINNIN_PHILOSOPHERS_FILES})
target_link_libraries(07_dinning_philosophers PRIVATE Catch2::Catch2WithMain)

if(BUILD_TESTING)
    add_subdirectory(tests/libhellotest)
    add_subdirectory(tests/libgoodbyetest)
endif()
