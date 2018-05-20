# prog 3
prog3已按照要求实现.
其中, 单元测试使用next_permutation算法, 
测试了自然数1-n的全排列, 
以及若干个0和若干个1的全排列. 
最后, 随机生成了一个长度为1000的数组测试, 
基本可以保证正确性.
# Chapter 8
1. 可以. 可以在stack中记录size信息, push/pop时相应更新, 在pop前检查stack是否为空即可.
2. 当pop一个空栈时, 我们会将bottom給pop出来, 再次pop会出现访问越界.
3. 如果back增长到capacity时, 继续enq, 可以让其发生回卷到0. 计算size时, 若back < front, 
   size=back+capacity - front. 这样, 我们可以充分利用空间
4. 可以. 在没有回卷时, 不浪费这一个元素完全可行. 但是如果需要实现回卷, 由于back=front时,
   可能意味着size=n或者size=0, 出现了歧义, 需要其他方式判别, 使得程序复杂化
5. 可以让其动态增长. 当size=capacity时, 继续push, 就申请一个两倍大小的array, 将数据拷贝过来, 然后有new_capacity=2*size, 可以继续增长. 这样做, 可以保证均摊时间复杂度为O(1)
