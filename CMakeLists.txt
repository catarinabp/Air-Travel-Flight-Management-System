cmake_minimum_required(VERSION 3.26)
project(Projeto2AED)

set(CMAKE_CXX_STANDARD 17)

find_package(GTest REQUIRED)

add_executable(Projeto2AED main.cpp
        test.cpp)

target_link_libraries(Projeto2AED gtest::gtest)





