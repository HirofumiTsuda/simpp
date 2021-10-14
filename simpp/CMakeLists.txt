cmake_minimum_required(VERSION 3.16)
project(simpp CXX)


add_subdirectory(src)
add_subdirectory(test)

enable_testing()
add_test (NAME test COMMAND test_process)
