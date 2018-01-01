#include "monoid_tree.h"
// #include "../fenwick_tree/fenwick.h"
#include <gtest/gtest.h>

TEST(fenwick, base) {
  // for(int i = 0; i < N; i++){
  // 	for(int j = i; j < N; j++){
  // 		int result = tree.reduce(i, j);
  // 		int std_result = (j - i) ;
  // 		ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
  // 	}
  // }
  for (int k = 0; k < 10; ++k) {
    int N = 100000; 
    MonoidTree tree(N);
    // Fenwick tree(N);
    for (int i = 0; i < N; i++) {
      tree.raw_update(i, i + N);
    }
    tree.fast_init();
    for (int i = 0; i < N; i++) {
      for (long long j = i; j < N; j++) {
        long long result = tree.reduce(i, j);
				ASSERT_GT(result, -1);
        long long std_result = (i + j - 1 + 2 * N) * (j - i) / 2;
        ASSERT_EQ(std_result, result) << "i = " << i << "j = " << j;
      }
    }
  }
}
