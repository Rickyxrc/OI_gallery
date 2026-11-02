#import "../../../lib.typ": code-block

使用欧几里得算法：$gcd(a, b) = gcd(b, a mod b)$，直到 $b = 0$。

时间复杂度 $O(log min(a, b))$，空间复杂度 $O(1)$。

#code-block(read("b.cpp"))
