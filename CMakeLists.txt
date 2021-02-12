cmake_minimum_required(VERSION 3.17)

project(Debug20
VERSION 0.1
LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED 20)

add_subdirectory(external_dependecies)

add_subdirectory(src)