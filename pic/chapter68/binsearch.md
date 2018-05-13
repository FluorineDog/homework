# Exercise 1
## Inspiration
左闭右开区间实际上是编码规范的一部分. 
但是为了实现全闭空间, 我们将原来的hi替换为（hi+1）, 
再根据语法语义进行相应调整即可. 
## Code
参见 binsearch.c0的binsearch_inclusive

```c++
// exercise 1
int binsearch_inclusive(int x, int[] A, int n)
//@requires 0 <= n && n <= \length(A);
//@requires is_sorted(A, 0, n);
/*@ensures (-1 == \result && !is_in(x, A, 0, n))
|| ((0 <= \result && \result < n) && A[\result] == x);
@*/
{
  int lo = 0;
  int hi = n - 1; // to be inclusive
  while (lo <= hi)
  //@loop_invariant 0 <= lo && hi < n;
  //@loop_invariant (lo == 0 || A[lo-1] < x);
  //@loop_invariant (hi == n - 1 || A[hi + 1] > x);
  {
    //@assert lo <= hi;
    int mid = lo + (hi + 1 - lo) / 2;
    //@assert lo <= mid && mid <= hi;
    if (A[mid] == x)
      return mid;
    else if (A[mid] < x)
      lo = mid + 1;
    else /*@assert(A[mid] > x);@*/
      hi = mid - 1;
  }
  return -1;
}
```

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

```c++
// exercise 2
int binsearch(int x, int[] A, int n)
//@requires 0 <= n && n <= \length(A);
//@requires is_sorted(A, 0, n);
/*@ensures (-1 == \result && !is_in(x, A, 0, n))
|| ((0 <= \result && \result < n) && A[\result] == x);
@*/
{
  int lo = 0;
  int hi = n;
  while (lo < hi)
  //@loop_invariant range_checker(lo, hi, n);
  //@loop_invariant is_in(x, A, lo, hi) == is_in(x, A, 0, n);
  {
    int mid = lo + (hi - lo) / 2;
    //@assert lo <= mid && mid < hi;
    if (A[mid] == x){
      return mid;
    }
    else if (A[mid] < x){
      //@assert !is_in(x, A, lo, mid + 1);
      lo = mid + 1;
    }
    else {
      //@assert !is_in(x, A, mid, hi);
      /*@assert(A[mid] > x);@*/
      hi = mid;
    }
  }
  return -1;
}
```

## Proof
新的证明如下

0. 循环不变量是将is_in(x, A, lo, hi) = is_in(x, A, 0, n);
1. 在进入循环体前, 有初始条件 lo = 0, hi = n, 不变量显然成立
2. 循环体内mid = lo + (hi - lo) / 2; 数学上可以保证 
   lo <= mid && mid < hi, 从而lo单调不减, hi单调不增. 
4. 如果A[mid] == x 时, 我们找到了, 返回当前mid即可, 终止而正确
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

# Exercise 3
## Code 
参见 binsearch.c0的binsearch_standard

```c++
// exercise 3
int binsearch_standard(int x, int[] A, int n)
//@requires 0 <= n && n <= \length(A);
//@requires is_sorted(A, 0, n);
//@ensures \result == 0 || A[\result - 1] < x;
//@ensures \result == n || x <= A[\result];
{
  int lo = 0;
  int hi = n;
  while(lo < hi)
  //@loop_invariant range_checker(lo, hi, n);
  //@loop_invariant lo == 0 || A[lo] < x;
  //@loop_invariant hi == n || x <= A[hi];
  {
    int mid = lo + (hi - lo) / 2;
    //@assert lo <= mid && mid < hi;
    if(A[mid] < x){
      lo = mid + 1;
      //@assert A[lo - 1] < x;
    }
    else {
      hi = mid;
      //@assert x <= A[hi];
    }
  }
  //@assert lo == hi;
  return lo;
}
```
## Proof
0. 循环不变量: 将lo[-1]看作负无穷大, 将hi[n]看作正无穷大, 有
   A[lo - 1 ] < x <= A[hi]
1. 初始条件, 有lo = 0, hi = n, 循环不变量显然成立
2. mid = lo + (hi - lo) / 2, 有mid ∈ [lo, hi)
3. 当A[mid] < x时, x <= A[hi]性质被继承, 而将lo替换为mid+1后,
   A[lo - 1] = A[mid] < x成立, 循环不变量继续保持
4. 当A[mid] < x时, A[lo-1] < x性质被继承, 而将hi 替换为mid后,
   A[hi] = A[mid] >= x成立, 循环不变量继续保持
5. mid ∈ [lo, hi), 而要么有lo = mid = 1, 要么有hi = mid, 区间严格缩小
   程序会终止在lo == hi处
6. 最后\result=lo=hi, 满足不变量性质即为满足题设条件.