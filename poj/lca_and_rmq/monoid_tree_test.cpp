#include <gtest/gtest.h>
#include "monoid_tree.h"
TEST(fenwick, base){
	MonoidTree tree(100);
	// for(int i = 0; i < 100; i++){
	// 	for(int j = i; j < 100; j++){
	// 		int result = tree.reduce(i, j);	
	// 		int std_result = (j - i) ;
	// 		ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
	// 	}
	// }
	for(int i = 0; i < 100; i++){
		tree.raw_update(i, i+100);	
	}
	tree.fast_init();
	for(int i = 0; i < 100; i++){
		for(int j = i; j < 100; j++){
			int result = tree.reduce(i, j);	
			int std_result = (i + j - 1 + 200) * (j - i) / 2 ;
			ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
		}
	}
}
