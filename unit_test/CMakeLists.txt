cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE debug)
include_directories(../src)


add_executable(test_comport test_comport.cpp)
add_executable(test_rbtree test_rbtree.cpp)

