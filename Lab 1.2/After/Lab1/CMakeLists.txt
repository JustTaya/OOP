cmake_minimum_required(VERSION 3.13)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp catch.hpp IPAddress.cpp IPAddress.h IPFactory.h IP.h IPParser.cpp IPParser.h test.cpp)