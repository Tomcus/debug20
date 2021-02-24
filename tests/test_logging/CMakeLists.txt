add_executable(test-logging test_logging.cpp)

target_link_libraries(test-logging debug20)

add_test(NAME "TestLogging" COMMAND test-logging)