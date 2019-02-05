cmake_minimum_required(VERSION 2.6)
project(red_black_tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_C_COMPILER "${COMPILER}gcc")
set(CMAKE_CXX_COMPILER "${COMPILER}g++")

add_executable(red_black_tree
	main.cpp
	RedBlackTree.cpp
)


set_target_properties(red_black_tree PROPERTIES OUTPUT_NAME "${EXECUTABLE_NAME}")
