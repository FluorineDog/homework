project(suffix_array_tree)
set(CXX_STANDARD 17)
add_executable(suffix_array_test suffix_array_test.cpp)
target_link_libraries(suffix_array_test gtest gtest_main)
