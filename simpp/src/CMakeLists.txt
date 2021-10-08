find_package(Boost REQUIRED COMPONENTS context)

add_library(simpp
  STATIC
  allof.cpp
  anyof.cpp
  condition.cpp
  core.cpp
  event.cpp
  process.cpp
  queue_event.cpp
  timeout.cpp
)

if(Boost_FOUND)
  target_include_directories(simpp PUBLIC ${Boost_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include )
  target_link_libraries(simpp ${Boost_LIBRARIES} )
  target_compile_options(simpp PUBLIC -lboost_context -O2 -Wall)
  target_compile_features(simpp PUBLIC cxx_std_17)
endif(Boost_FOUND)
  
