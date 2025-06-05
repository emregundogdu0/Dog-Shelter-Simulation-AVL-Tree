cmake_minimum_required(VERSION 3.29)
project(treeproject C)

set(CMAKE_C_STANDARD 99)

add_executable(treeproject
        shelterApp.c
        avltree.c
)
