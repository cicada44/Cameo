cmake_minimum_required(VERSION 3.22)

project(
    "Cameo"
    VERSION 0.9
    LANGUAGES CXX
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)

find_package(OpenCV REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(external)
