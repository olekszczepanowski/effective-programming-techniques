cmake_minimum_required(VERSION 3.26)
project(lab5)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab5 main.cpp
        CString.cpp
        CString.h
        CConsole.h
        CNode.h
        CTree.h
        CRefCounter.h
        CMySmartPointer.h
)
