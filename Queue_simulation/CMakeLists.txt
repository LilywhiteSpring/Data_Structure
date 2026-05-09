cmake_minimum_required(VERSION 4.0)
project(Queue_simulation)

set(CMAKE_CXX_STANDARD 20)

add_executable(Queue_simulation main.cpp
        simulation.h
        simulation.cpp)
