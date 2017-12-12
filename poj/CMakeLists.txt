cmake_minimum_required(VERSION 3.5)
project(poj)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS off)
add_compile_options(-std=c++98 -Werror -Wall)
add_definitions(-DDOG_DEBUG)
add_subdirectory(disjoint_set)