cmake_minimum_required(VERSION 3.1)
project(matrix)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp fdeque.cpp)
add_executable(matrix ${SOURCE_FILES} FDequeIterator.cpp FDequeIterator.h Node.cpp Node.h)