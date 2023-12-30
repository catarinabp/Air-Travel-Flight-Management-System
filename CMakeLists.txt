cmake_minimum_required(VERSION 3.26)
project(Projeto2AED)

set(CMAKE_CXX_STANDARD 17)

set( CMAKE_BUILD_TYPE_TMP "${CMAKE_BUILD_TYPE}" )
set( CMAKE_BUILD_TYPE "Release" )
add_subdirectory(googletest)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

add_executable(Projeto2AED main.cpp
        test.cpp)

target_link_libraries(Projeto2AED gtest gtest_main)





