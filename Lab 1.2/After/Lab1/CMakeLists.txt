cmake_minimum_required(VERSION 3.13)
project(Lab1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab1
        BinTree.inc
        BSTree.inc
        catch.hpp
        CMakeLists.txt
        Convert.h
        IPAddress.cpp
        IPAddress.h
        main.cpp
        MultiTree.inc
        Samples.h
        Tree.h
        IP.h
        IP.cpp)
