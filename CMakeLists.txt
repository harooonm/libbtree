cmake_minimum_required(VERSION 2.8.9)
project(libbtree)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wfatal-errors -std=c11")

if(CMAKE_BUILD_TYPE EQUAL "Debug")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Og")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
endif()

include_directories(include)
add_library(btree SHARED "src/btree.c")
set_property(TARGET btree PROPERTY POSITION_INDEPENDENT_CODE ON)
