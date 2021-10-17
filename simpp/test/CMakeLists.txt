# To use the googletest
find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(test_timeout timeout_test.cpp)

target_link_libraries(test_timeout simpp GTest::GTest GTest::Main)

gtest_discover_tests(test_timeout)
