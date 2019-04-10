cmake_minimum_required(VERSION 3.12.1)
project(os_find)

set(CMAKE_CXX_STANDARD 14)

add_executable(os_find Filter.h
        Filter.cpp
        Visitor.cpp
        Visitor.h
        Launcher.h
        flfinder.cpp Launcher.h)