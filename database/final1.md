-----
documentclass:
  -ctexart
  -fontenc

-----

# Chapter 2
## 2.6
![2.6 result](pic/2.6-result.png)

## 2.7
自然连接是以共享的分量为等值条件的等值连接, 同时额外使用投影去除重复分量

## 2.8
基本的操作有$\sigma, \times, \Pi ,-$
其余操作有(注意, 为了方便书写, 我们可以使用已经实现的算子实现其后的操作)

$$A \cap B = A - (A - B)$$
$$\neg A = U - A$$
$$ A \cup B = U - (\neg A)\cap(\neg B) $$ 
$$ A \bowtie_{cond} B = \sigma_{cond}(A \times B) $$
$$ A \bowtie B = \Pi_{attr(A) \cup attr(B)}(\sigma_{A[attr(A)\cap attr(B)] = B[attr(A)\cap attr(B)]}(A\times B)) $$

