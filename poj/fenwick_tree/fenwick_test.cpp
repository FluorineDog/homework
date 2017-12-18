#include <gtest/gtest.h>
#include "fenwick.h"
TEST(fenwick, base){
	Fenwick tree(100);
	for(int i = 0; i < 100; i++){
		for(int j = i; j < 100; j++){
			int result = tree.reduce(i, j);	
			int std_result = (j - i) ;
			ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
		}
	}
	for(int i = 0; i < 100; i++){
		tree.update(i, i+100);	
	}
	for(int i = 0; i < 100; i++){
		for(int j = i; j < 100; j++){
			int result = tree.reduce(i, j);	
			int std_result = (i + j - 1 + 200) * (j - i) / 2 ;
			ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
		}
	}
}
