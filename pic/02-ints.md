1. 见02-ints.c0中的quot和rem，按照truncate to 0实现。
   计算quot(INT_MIN, -1)时，会发生溢出，
   为此我在quot的requires中加上了限制。
2. 见02-ints.c0中的代码，为避免与标准库的冲突，改为int2hex_dog函数。
3. 见02-ints.c0中的lsr函数。由于shift>=32是未定义行为，不予处理。
   在补码上看，lsr(x, 1)等价于取了x的二进制表示的高31位。