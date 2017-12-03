cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 98)

set(SOURCE_FILES main.cpp)
add_executable(server ${SOURCE_FILES})