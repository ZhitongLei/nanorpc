project(nanorpc)
cmake_minimum_required(VERSION 3.6)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -static-libgcc -static-libstdc++")
#if(CMAKE_BUILD_BITS EQUAL 32)
#  list(APPEND CMAKE_CXX_FLAGS "-m32")
#endif()
#set(CMAKE_BUILD_TYPE Debug)
# we can create Makefile for debug or release: cmake -DCMAKE_BUILD_TYPE=Release ${project-path}
#set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -Wall")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(
    ./third_party/protobuf/include
    ./third_party/nanomsg/include
)
include_directories(${PROJECT_SOURCE_DIR}/src)
link_directories(
    /usr/local/lib
    /usr/lib
    /usr/lib64
    ./third_party/protobuf/lib
    ./third_party/nanomsg/lib64
)
 
add_subdirectory(${PROJECT_SOURCE_DIR}/src/util)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/net)
add_library(nanorpc)
target_link_libraries(nanorpc nanorpc_net nanorpc_util)
#aux_source_directory(./src/net SRC_LIST)
#aux_source_directory(${PROJECT_SOURCE_DIR} SRC_LIST)
#add_library(nanorpc ${SRC_LIST})
#target_link_libraries(nanorpc libprotobuf.a)
#target_link_libraries(nanorpc nanomsg)

if(CMAKE_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
