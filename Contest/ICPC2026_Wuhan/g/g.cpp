#include <stdio.h>
#define maxn 200007

typedef long long i64;
typedef __int128 i128;

int T;
int n;
i64 k, li[maxn], s;

inline i64 max(i64 a, i64 b) { return a > b ? a : b; }
inline i64 min(i64 a, i64 b) { return a < b ? a : b; }

bool check(i64 p) {
    // m = 0，公式不适用
    if (p < n) {
        i64 cnt_pos = 0;
        for (int i = 1; i <= n; i++)
            if (li[i] >= 1)
                cnt_pos++;
        return p <= cnt_pos + k;
    }

    i64
        // 完整的块数
        blocks = (p - 1) / (n - 1),
        // 此外剩余的数量
        remain = (p - 1) % (n - 1),
        // 每首曲目（实际）最少的出现次数
        min_played = (blocks + 1) / 2,
        // 单曲实际抵扣的最大数量
        max_discount = blocks / 2;

    i64 waste_cards = 0, capped = 0, cnt_big = 0;
    for (int i = 1; i <= n; i++) {
        // 这里若 d>=0，实际含义是我的播放次数多于最少的次数，
        // 这些卡片也就被“浪费”了
        i64 d = max(li[i] - min_played, 0);
        waste_cards += d;

        // ceil(m/2) + floor(m/2) = m，所以说多出来的部分就是浪费的，但是 capped
        // 记录的部分是“实际没有浪费的卡片”
        capped += min(d, max_discount);

        // blocks+1 意味着可以到最后剩余的部分
        if (li[i] >= blocks + 1)
            cnt_big++;
    }

    // 在剩余的部分内，如果有能播放的曲目，这些卡片也不是“浪费”的
    capped += min(remain, cnt_big);

    i64 ini_waste = p - n * min_played;
    i64 waste = waste_cards - min(ini_waste, capped);

    return p <= k + s - waste;
}

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%lld", &n, &k);

        s = 0;
        for (int i = 1; i <= n; i++)
            scanf("%lld", li + i), s += li[i];

        i64 l = 0, r = 1e18;
        while (r - l) {
            i64 mid = (l + r + 1) >> 1;
            if (check(mid))
                l = mid;
            else
                r = mid - 1;
        }

        printf("%lld\n", l);
    }
    return 0;
}