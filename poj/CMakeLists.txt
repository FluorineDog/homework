cmake_minimum_required(VERSION 3.5)
project(poj)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_EXTENSIONS off)
# no -pedantic since c++98 DONOT support long long 
add_compile_options(-Werror -Wall)
add_definitions(-DDOG_DEBUG)
add_definitions(-D_GLIBCXX_DEBUG)
add_subdirectory(disjoint_set)
add_subdirectory(fenwick_tree)
add_subdirectory(suffix_array)
add_subdirectory(lca_and_rmq)
add_subdirectory(segment_tree)
