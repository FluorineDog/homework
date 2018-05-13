# Exercise 1
1. 
see qsort.c0 > is_permutation
```c++
bool is_permutation(int[] arr, int abeg, int aend,  //
                    int[] brr, int bbeg, int bend)
//@requires range_checker(abeg, aend, \length(arr));
//@requires range_checker(bbeg, bend, \length(brr));
{
  for (int iter = abeg; iter < aend; iter += 1) {
    int count_a = 0;
    int count_b = 0;
    int x = arr[iter];
    for (int i = abeg; i < aend; i += 1) {
      if(arr[i] == x) count_a += 1;
    }
    for (int i = bbeg; i < bend; i += 1) {
      if(brr[i] == x) count_b += 1;
    }
    if(count_a != count_b) return false;
  }
  return true;
}
```

2. see qsort.c0, main difference is the following:
```c++
//...
{
  int[] A_copy = alloc_array(int , upper - lower);
  //...
  //@assert is_permutation(A_copy, 0, upper - lower, A, lower, upper);
}
```
3. 由于排序是本地的, 在排序结束后不能获取原始数组, 
   因此我们不得不在函数开始前复制一份镜像. 
   时间复杂度依然是O(nlogn), 但是空间复杂度从O(logn)变为了O(n).
  
# Exercise 2
当 upper - lower = 1 时, 显然成立
假设证明upper - lower <= K - 1 时, qsort结果正确
那么对于qsort过程, 
1. 首先进行partition, 有pivot左边的元素全部都小于等于pivot, 
   pivot右边的元素都大于等于pivot
2. 对左边元素和右边的元素分别进行qsort, 由递归条件, 
   分别让左边的元素有序, 以及右边的元素有序.
3. 以上所有的操作都保证is_permutation性质成立, 因此最后is_permutation也成立.
4. 由于左边元素有序, 左边元素都大于pivot, 从而都大于右边元素, 右边元素也有序且大于pivot
   因此整体有序
# Exercise 3
// choose the first middle
[5, 3, 1, 0, 2, 4, 6]

# Exercise 4


