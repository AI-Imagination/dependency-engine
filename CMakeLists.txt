cmake_minimum_required(VERSION 3.2)
project(VisualDL)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-fPIC")

################################ Configurations #######################################
set(THIRD_PARTY_PATH "${CMAKE_BINARY_DIR}/third_party" CACHE STRING
        "A path setting third party libraries download & build directories.")

include(external/zlib)      # download, build, install zlib
include(external/gflags)
include(external/glog)
include(external/gtest)     # download, build, install gtest
include(external/eigen)     # download, build, install gtest


include_directories(${PROJECT_SOURCE_DIR})

add_library(engine ${PROJECT_SOURCE_DIR}/engine.cc)
add_dependencies(engine glog)

# add_executable(engine_test ${PROJECT_SOURCE_DIR}/engine_test.cc)
# target_link_libraries(engine_test engine glog)
