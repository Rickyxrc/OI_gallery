#import "../../../lib.typ": code-block

status: `null`

题目等价的意思是：对于任意两个数 $a, b in A, (a<b)$，要么 $a perp b$，要么 $a | b$。

这道题我本来想的是这样一个性质：

$ "let" c = product_(i=1)^n a_i, forall i in [1,n], c perp a_i $

但是构造质因子连乘明显乘爆炸，而且不满足我们题目加法的数量限制。

不过这之中有一个相当重要的观察： $ gcd(a, b) = gcd(a, b-a) (b>a) $

后来发现这个 $a|b$ 可以退化到 $a = b$ 的情况。

然后经过 itshawn 点拨，发现任何一个质数的可重集合都满足上述的性质。

所以，只需要对于每个数字都找到大于等于它的质数就好了。

#code-block(read("c1.cpp"))
