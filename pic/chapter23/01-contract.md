1. 见代码01-contract.c0 (注意：由于没有方法检测函数是否会同时出现error，
   我使用了magic_number作为溢出后的返回值来检测, 方便自动化测试。
   使用此方法时，只需取消return magic_number;的注释即可)
2. f(2, 2)在计算过程中会出现r=2的情况，不满足条件，会出现error
