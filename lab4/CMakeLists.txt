cmake_minimum_required(VERSION 3.26)
project(lab4)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab4 main.cpp
        cmake-build-debug/CTree.cpp
        cmake-build-debug/CTree.h
        cmake-build-debug/CNode.cpp
        cmake-build-debug/CNode.h
        cmake-build-debug/CConsole.cpp
        cmake-build-debug/CConsole.h)
