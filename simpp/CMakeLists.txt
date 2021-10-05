cmake_minimum_required(VERSION 3.16)
project(simpp CXX)

find_package(Boost REQUIRED COMPONENTS context)


add_library(simpp allof.cpp anyof.cpp condition.cpp core.cpp event.cpp process.cpp queue_event.cpp timeout.cpp)
add_executable(test test.cpp)
if(Boost_FOUND)
  target_include_directories(test PUBLIC ${Boost_INCLUDE_DIRS})
  target_link_libraries(test PRIVATE ${Boost_LIBRARIES} simpp)
  target_compile_options(test PUBLIC -lboost_context -O2 -Wall)
  target_compile_features(test PUBLIC cxx_std_17)  
endif(Boost_FOUND)

