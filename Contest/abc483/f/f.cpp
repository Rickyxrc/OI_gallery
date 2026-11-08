#include <map>
#include <stdio.h>

#define maxn 500107

typedef long long i64;
typedef std::pair<int, int> pii;

int n, u, v, q, x;

std::map<pii, int> mp;

i64 diff[maxn], s;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &u, &v), mp[{u, v}]++, s += u;

    for (auto [A, r] : mp) {
        auto [a, b] = A;

        for (int v = 0;; v++) {
            int lb = max(0, v * b - a);
            int rb = (v + 1) * b - a - 1;

            if (rb < 0)
                continue;

            if (lb >= maxn)
                break;

            diff[lb] += 1ll * v * r * b;
            if (rb + 1 < maxn)
                diff[rb + 1] -= 1ll * v * r * b;
        }
    }

    for (int i = 1; i < maxn; i++)
        diff[i] += diff[i - 1];

    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        scanf("%d", &x);
        printf("%lld\n", 1ll * n * x + s - diff[x]);
    }

    return 0;
}