cmake_minimum_required(VERSION 4.0)
project(Maze)

set(CMAKE_CXX_STANDARD 20)

add_executable(Maze main.cpp
        maze.h
        maze.cpp)
