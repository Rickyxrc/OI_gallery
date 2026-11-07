#include <algorithm>
#include <cstdio>
#include <stdio.h>

typedef long long i64;
#define maxn 400007

int T, n, k;
int li[maxn], arr[maxn];

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &k);
        k = n - k; // unpleasent num

        for (int i = 1; i <= n; i++)
            scanf("%d", li + i);

        std::sort(li + 1, li + n + 1);
        std::reverse(li + 1, li + 1 + k);

        for (int i = 1; i <= k; i++)
            li[n + i] = li[i];

        for (int i = 1; i <= n; i++)
            arr[i] = li[i + k];

        int f = 0;
        i64 s = 0;

        for (int i = 1; i <= n; i++) {
            if (s <= 1ll * arr[i] * (i - 1))
                f++;
            s += arr[i];
        }

        if (f == n - k) {
            puts("YES");
            for (int i = 1; i <= n; i++)
                printf("%d ", arr[i]);
            puts("");
        } else {
            puts("NO");
        }
    }

    return 0;
}