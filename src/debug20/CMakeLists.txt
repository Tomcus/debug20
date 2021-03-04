add_library(debug20
	assert.cpp assert.hpp
	exception.cpp exception.hpp
	log.cpp log.hpp
	backtrace.cpp backtrace.hpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	target_link_options(debug20 PUBLIC -rdynamic)
endif()

target_link_libraries(debug20 PUBLIC fmt source_location)

target_compile_features(debug20 PUBLIC cxx_std_20)
target_compile_options(debug20 PRIVATE -Wall -Wextra -Wpedantic -Werror)
set_property(TARGET debug20 PROPERTY CXX_STANDARD 20)

target_include_directories(debug20 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)