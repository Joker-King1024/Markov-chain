cmake_minimum_required(VERSION 3.17)
project(untitled)

add_definitions(-std=c++11)

find_package(Eigen3 REQUIRED)
include_directories("/usr/include/eigen3")


set(CMAKE_CXX_STANDARD 14)

add_executable(untitled main.cpp rand.h rand.cpp)