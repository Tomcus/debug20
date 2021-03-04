cmake_minimum_required(VERSION 3.17)

project(Debug20
VERSION 0.2
LANGUAGES CXX)

# if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set(CMAKE_VERBOSE_MAKEFILE ON)
# endif()

add_subdirectory(external_dependecies)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)