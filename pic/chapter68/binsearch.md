# Exercise 1
## Inspiration
左闭右开区间实际上是编码规范的一部分. 
但是为了实现全闭空间, 我们将原来的hi替换为（hi+1）, 
再根据语法语义进行相应调整即可. 
## Code
参见 binsearch.c0的binsearch_inclusive
## Proof
新的证明如下

0. 循环不变量是将A[-1] 看作无穷小, 将A[\length(A)]看作无穷大, 
   有A[lo - 1] < x && x < A [hi + 1]
1. 在进入循环体前, 有初始条件 lo = 0, hi = n-1, 不变量显然成立
2. 循环体内, 保证lo <= hi, 也就是待选区间[lo, hi]不空
3. mid = lo + (hi + 1 - lo) / 2; 数学上可以保证 
   lo <= mid && mid <= hi, 从而lo单调不减, hi单调不增. 
4. 如果A[mid] == x 时, 我们找到了, 返回当前mid即可
5. 如果A[mid] > x, 我们选择[lo, mid - 1]作为新的搜索区间. 
   此时, A[lo - 1] < x性质被继承, A[hi + 1] = A[mid] > x刚好被满足, 循环不变量继续成立
5. 如果A[mid] < x, 我们选择[mid + 1, hi]作为新的搜索区间. 
   此时, A[hi] > x性质被继承, A[mid - 1 ] = A[mid] < x刚好被满足, 循环不变量继续成立
6. 由于mid ∈ [lo, hi], 而lo会被mid + 1 替换, 
   hi会被mid - 1替换, 因此待选区间一定在严格缩小, 因此循环最后会终止.
7. 由于A数组是排好了序的, 所以当循环不变量满足时, 
   一定有is_in(x, A, 0, n) = is_in(x, A, lo, hi - 1), 
   所以循环不变量保证了函数的正确性.

# Exercise 2
## Code
参见 binsearch.c0的binsearch
## Proof
新的证明如下

0. 循环不变量是将is_in(x, A, lo, hi) = is_in(x, A, 0, n);
1. 在进入循环体前, 有初始条件 lo = 0, hi = n, 不变量显然成立
2. 循环体内mid = lo + (hi - lo) / 2; 数学上可以保证 
   lo <= mid && mid < hi, 从而lo单调不减, hi单调不增. 
4. 如果A[mid] == x 时, 我们找到了, 返回当前mid即可
5. 如果A[mid] < x, 我们选择[mid + 1, hi)作为新的搜索区间. 
   此时, 由于有序性, false = is_in(x, A, lo, mid + 1)是满足的, 则
   is_in(x, A, lo, hi) = is_in(x, A, lo, mid + 1) || is_in(x, A, mid + 1, hi)
      = is_in(x, A, mid + 1, hi), 将lo替换为mid + 1循环不变量继续保持
6. 如果x < A[mid], 我们选择[lo, mid)作为新的搜索区间. 
   此时, 由于有序性, false = is_in(x, A, mid, hi)是满足的, 则
   is_in(x, A, lo, hi) = is_in(x, A, lo, mid) || is_in(x, A, mid, hi)
      = is_in(x, A, lo, mid), 将hi替换为mid 循环不变量继续保持
7. 由于mid ∈ [lo, hi), 而要么lo会被mid + 1 替换, 
   要么hi会被mid替换, 因此待选区间一定在严格缩小, 因此循环最后会终止.

