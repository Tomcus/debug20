add_executable(test-asserts test_asserts.cpp)

target_link_libraries(test-asserts debug20)

add_test(NAME "TestingAssertions" COMMAND test-asserts)