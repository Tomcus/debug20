add_library(source_location INTERFACE)

target_sources(source_location PUBLIC source_location.hpp)

# target_include_directories(source_location PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)