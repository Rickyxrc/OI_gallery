#include <stdio.h>

typedef long long i64;
inline i64 max(i64 a, i64 b) { return a > b ? a : b; }
inline i64 min(i64 a, i64 b) { return a < b ? a : b; }

#define maxn 200007

i64 li[maxn], s[maxn], lmn[maxn], lmx[maxn], rmn[maxn], rmx[maxn];
int n;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", li + i), s[i] = li[i] + s[i - 1];

    lmn[0] = lmx[0] = 0;
    rmn[n + 1] = 1ll << 60;
    rmx[n + 1] = -(1ll << 60);

    for (int i = 1; i <= n; i++)
        lmn[i] = min(s[i], lmn[i - 1]), lmx[i] = max(s[i], lmx[i - 1]);
    for (int i = n; i >= 1; i--)
        rmn[i] = min(s[i], rmn[i + 1]), rmx[i] = max(s[i], rmx[i + 1]);

    i64 ans = (lmx[n] - lmn[n] + 1);
    for (int i = 1; i <= n; i++) {
        ans = max(ans, max(lmx[i - 1], rmx[i] - 2 * li[i]) -
                           min(lmn[i - 1], rmn[i] - 2 * li[i]) + 1);
    }

    printf("%lld", ans);

    return 0;
}