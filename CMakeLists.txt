cmake_minimum_required(VERSION 3.22)
project(Project02)

set(CMAKE_CXX_STANDARD 14)

include_directories(./)
add_executable(Project02 main.cpp operators.cpp utils.cpp)
