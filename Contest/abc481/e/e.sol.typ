#import "../../../lib.typ": code-block

考虑一条旋转的直线，扫描维护直线两端的点。
容易说明，旋转一圈之后，所有情况都能考虑到。

这题我在考场上卡了排序，意思是元素必须要有稳定的相对顺序。
什么意思呢？就是像这道题，斜率会有正负无穷的情况，此时我之前忽略了它们，那可能就会影响排序。
所以，以下 `cmp` 函数中的前面部分不能省略，它代表将这些值放在数组的两端。

```cpp
bool cmp(const s &a, const s &b) {
  if (a.x == 0)
    return true;
  if (b.x == 0)
    return false;

  // a.y/a.x - b.y/b.x < 0;
  // ay bx - ax by < 0 ()rev if ax bx < 0
  i64 r = 1ll * a.y * b.x - 1ll * a.x * b.y;

  if (1ll * a.x * b.x > 0)
    return r < 0;
  else
    return r > 0;
}
```

代码不难，思维也不难，就做一个简单的记录。

#code-block(read("e.cpp"))
