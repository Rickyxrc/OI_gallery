#include <algorithm>
#include <numeric>
#include <stdio.h>
#include <vector>

#define maxn 200007
char check[maxn];
int prime[maxn], cnt, n, q, Tp, li[maxn];
int f[maxn], rev[maxn], dis[maxn];

void ola_prime() {
    for (int i = 2; i < maxn; i++) {
        if (!check[i])
            prime[++cnt] = i;
        for (int j = 1; j <= cnt; j++) {
            if (i * prime[j] >= maxn)
                break;
            check[i * prime[j]] = 1;
            if (!(i % prime[j]))
                break;
        }
    }
    return;
}

std::vector<int> traces;
void trace(int x) {
    if (x == 0)
        return;
    traces.push_back(rev[x]);
    trace(x - rev[x]);
}

int T;
int main() {
    ola_prime();
    scanf("%d", &T);

    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);

        if (a == b) {
            puts("0");
            continue;
        }
        if (std::gcd(b - a, a) == 1) {
            printf("1\n%d\n", b - a);
            continue;
        }

        auto ansp = std::upper_bound(prime + 1, prime + cnt + 1, a);
        auto ans = *ansp;

        int fr = 0;
        while (ans < b) {
            if (ans < b and (std::gcd(ans - a, a) == 1) and
                (std::gcd(b - ans, b) == 1)) {
                fr = 1;
                printf("2\n%d %d\n", ans - a, b - ans);
                break;
            }
            ansp++;
            ans = *ansp;
        }

        if (not fr) {
            f[0] = 1;
            for (int i = 1; i <= b - a; i++)
                f[i] = 0, rev[i] = 0, dis[i] = 100;

            dis[0] = 0;
            for (int i = 0; i <= b - a; i++)
                if (f[i])
                    for (int d = b - a - i; d >= 1; d--)
                        if (std::gcd((a + i), d) == 1 and
                            dis[i] + 1 < dis[i + d])

                            dis[i + d] = dis[i] + 1, rev[i + d] = d,
                                    f[i + d] = 1;

            traces.clear();
            trace(b - a);

            printf("%zu\n", traces.size());
            for (auto it = traces.rbegin(); it != traces.rend(); it++)
                printf("%d ", *it);
            puts("");
        }
    }
    return 0;
}