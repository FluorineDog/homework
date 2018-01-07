cmake_minimum_required(VERSION 3.5)
add_library(md5 SHARED md5.cpp)
target_link_libraries(md5 ssl)
# add_executable(dog_test dog_test.cpp)