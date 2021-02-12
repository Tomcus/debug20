add_library(debug20
	assert.cpp assert.hpp
	exception.cpp exception.hpp
	log.cpp log.hpp
)

target_link_libraries(debug20 PRIVATE fmt)

target_include_directories(debug20 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)