#include <stdio.h>
typedef long long i64;
typedef __int128_t i128;

i64 n, res;

inline i64 mulmx(int c, int m, int k) {
    i128 res = 1;
    for (int i = 1; i <= c; i++) {
        res *= m + i128((i - 1)) * k;
        if (res > n)
            return n + 1;
    }
    return res;
}

inline i64 pow(i64 x, int c) {
    i128 ans = 1;
    for (int i = 1; i <= c; i++) {
        ans *= x;
        if (ans > n)
            return n + 1;
    }
    return ans;
}

i64 nsq(i64 x, int c) {
    i64 l = 1, r = x;
    while (r - l > 1) {
        i64 mid = (l + r) >> 1;
        if (pow(mid, c) > x)
            r = mid - 1;
        else
            l = mid;
    }

    if (pow(r, c) > x)
        return l;
    else
        return r;
}

int main() {

    scanf("%lld", &n);

    for (int pw = 3; pw <= 20; pw++) {

        i64 ns = nsq(n, pw);
        if (mulmx(pw, 1, 1) > n) {
            break;
        }

        for (int m = 1; m <= ns; m++) {
            if (mulmx(pw, m, 1) > n) {
                break;
            }

            i64 l = 1, r = 1;
            while (mulmx(pw, m, r) <= n)
                r <<= 1;

            while (r - l > 1) {
                i64 mid = (l + r) >> 1;

                if (mulmx(pw, m, mid) > n)
                    r = mid - 1;
                else
                    l = mid;
            }

            i64 ans = -1;
            if (mulmx(pw, m, r) > n)
                ans = l;
            else
                ans = r;


            res += ans;
        }
    }

    printf("%lld", res);
    return 0;
}
