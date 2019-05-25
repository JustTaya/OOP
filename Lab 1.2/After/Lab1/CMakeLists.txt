cmake_minimum_required(VERSION 3.13)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(Lab1 main.cpp
        test.cpp
        catch.hpp
        IPAddress.h IPAddress.cpp
        IP.h IP.cpp
        IPParser.h IPParser.cpp
        IPFactory.h IPFactory.cpp
        IPConvertor.h IPConvertor.cpp
        IPComparator.h IPComparator.cpp
        SubNetwork.h SubNetwork.cpp
        Tree.h
        TreeNode.h
        TreeIterator.h
        )