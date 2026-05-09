cmake_minimum_required(VERSION 4.0)
project(Link_graph)

set(CMAKE_CXX_STANDARD 20)

add_executable(Link_graph main.cpp
        "Linkgraph(undirected).h"
        "Linkgraph(directed).h")
