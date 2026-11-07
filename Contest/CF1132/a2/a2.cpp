#include <stdio.h>
typedef long long i64;

#define maxn 107

int T;
int n, a[maxn];
int f[maxn];
int cnt[maxn], v, m, m1, m2;

int main() {
    scanf("%d", &T);
    while (T--) {
        m = 0;
        m1 = m2 = 0;
        for (int i = 0; i < 30; i++)
            cnt[i] = 0;

        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", &v), cnt[v]++;

        for (int i = 30; i >= 0; i--) {
            while (cnt[i]) {
                cnt[i]--;
                if (m1 <= m2)
                    m1 += 1 << i;
                else
                    m2 += 1 << i;
            }
        }

        printf("%lld\n", 1ll * (m1) * (m2));
    }

    return 0;
}