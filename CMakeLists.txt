cmake_minimum_required(VERSION 3.5.1)
project(ADdemo)

set(CMAKE_CXX_STANDARD 14)

add_executable(acc_demo main.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
