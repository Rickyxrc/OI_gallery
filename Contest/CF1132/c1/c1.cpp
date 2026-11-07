#include <algorithm>
#include <stdio.h>

#define maxn 200007
char check[maxn];
int prime[maxn], cnt, n, q, Tp, li[maxn];

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

int T;
int main() {
    ola_prime();
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++)
            scanf("%d", li + i);

        for (int i = 1; i <= n; i++)
            printf("%d ", *std::lower_bound(prime + 1, prime + cnt + 1, li[i]));
        puts("");
    }
    return 0;
}