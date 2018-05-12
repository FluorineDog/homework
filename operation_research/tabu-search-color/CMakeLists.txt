cmake_minimum_required(VERSION 3.11)
project(tabusearch)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS off)
# no -pedantic since c++98 DOES NOT support long long 
add_compile_options(-Werror -Wall -pedantic -Wno-unused-variable)
add_definitions(-DDOG_DEBUG)
# add_definitions(-DDOG_USE_SYSTEM_IOSTREAM)
add_definitions(-D_GLIBCXX_DEBUG)


add_executable(main main.cpp)


