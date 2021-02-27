add_library(source_location
    source_location.hpp source_location.cpp)

target_compile_features(source_location PUBLIC cxx_std_20)
target_compile_options(source_location PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_property(TARGET source_location PROPERTY CXX_STANDARD 20)
    
target_include_directories(source_location PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)