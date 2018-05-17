cmake_minimum_required(VERSION 3.4)
project(tabusearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
# no -pedantic since c++98 DOES NOT support long long 
add_compile_options(-Ofast -Werror -Wall -pedantic -Wno-unused)
add_definitions(-DDOG_DEBUG)
# add_definitions(-DDOG_USE_SYSTEM_IOSTREAM)
#add_definitions(-D_GLIBCXX_DEBUG)

add_executable(main searcher.cpp)
# add_executable(TS TS_algorithm.cc)
