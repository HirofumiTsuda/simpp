# To use the googletest
find_package(GTest REQUIRED)
include(GoogleTest)


# timeout
add_executable(test_timeout timeout_test.cpp)

target_link_libraries(
  test_timeout
  simpp
  GTest::GTest
  GTest::Main
  pthread
  )

gtest_discover_tests(test_timeout)

# AND / OR condition
add_executable(test_condition condition_test.cpp)

target_link_libraries(
  test_condition
  simpp
  GTest::GTest
  GTest::Main
  pthread
  )

gtest_discover_tests(test_condition)

# process
add_executable(test_interact interact_test.cpp)

target_link_libraries(
  test_interact
  simpp
  GTest::GTest
  GTest::Main
  pthread
  )

gtest_discover_tests(test_interact)
