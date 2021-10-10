cmake_minimum_required(VERSION 3.16)
project(simpp CXX)


add_subdirectory(src)

add_subdirectory(test)
enable_testing()
add_test(NAME test_process COMMAND test_process)
