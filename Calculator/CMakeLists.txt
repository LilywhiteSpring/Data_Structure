cmake_minimum_required(VERSION 4.0)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Calculator main.cpp
        calc.h
        calc.cpp)
