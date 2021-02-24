cmake_minimum_required(VERSION 3.17)

project(Debug20
VERSION 0.1
LANGUAGES CXX)

add_subdirectory(external_dependecies)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)