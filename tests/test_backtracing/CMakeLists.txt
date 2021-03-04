add_executable(test-backtrace test_backtrace.cpp)

target_link_libraries(test-backtrace debug20)

add_test(NAME "TestingBactracing" COMMAND test-backtrace)