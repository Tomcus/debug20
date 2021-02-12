add_library(debug20
	debug20/assert.cpp debug20/assert.hpp
	debug20/exception.cpp debug20/exception.hpp
	debug20/log.cpp debug20/log.hpp
)

target_link_libraries(debug20 PRIVATE fmt)

target_include_directories(debug20 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})