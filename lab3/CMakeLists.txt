cmake_minimum_required(VERSION 3.26)
project(lab3)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab3 main.cpp
        cmake-build-debug/CNode.cpp
        cmake-build-debug/CNode.h
        cmake-build-debug/CTree.cpp
        cmake-build-debug/CTree.h
        cmake-build-debug/CConsole.cpp
        cmake-build-debug/CConsole.h)
