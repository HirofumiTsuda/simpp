

add_executable(test_process test_process.cpp)

target_link_libraries(test_process simpp)

add_executable(test_timeout timeout_test.cpp)

target_link_libraries(test_timeout simpp)
