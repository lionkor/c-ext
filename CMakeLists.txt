cmake_minimum_required(VERSION 3.16) # for c++20

project(c-ext)

set(CMAKE_CXX_STANDARD 20)

if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -s")
endif()

add_executable(test src/test.cpp)

target_include_directories(test PRIVATE include)
