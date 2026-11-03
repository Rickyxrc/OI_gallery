#include <stdio.h>
#include <vector>
#define maxn 200007

const int mod = 998244353;

using namespace std;

int T, n;

int tsize[maxn], fas[maxn], prv[maxn], nxt[maxn], invs[maxn], facs[maxn],
    facsinv[maxn];
std::vector<int> edge[maxn];

inline int nointersect(int al, int ar, int bl, int br) {
    return max(al, ar) <= min(bl, br);
}

void dfs(int index) {
    tsize[index] = 1;
    for (auto v : edge[index])
        if (v != fas[index]) {
            dfs(v);
            if (not nointersect(prv[v], nxt[v], prv[index], nxt[index]))
                tsize[index] += tsize[v];
        }
}

int main() {
    invs[1] = 1;
    for (int i = 2; i < maxn; i++)
        invs[i] = (mod - (mod / i)) * 1ll * invs[mod % i] % mod;

    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);

        for (int i = 1; i <= n; i++)
            edge[i].clear(), tsize[i] = 0;

        for (int i = 2; i <= n; i++)
            scanf("%d", fas + i);
        for (int i = 1; i <= n; i++)
            scanf("%d", prv + i);
        for (int i = 1; i <= n; i++)
            scanf("%d", nxt + i);

        for (int i = 2; i <= n; i++)
            edge[fas[i]].push_back(i);

        dfs(1);

        int ans = 1;
        for (int i = 1; i <= n; i++)
            ans = 1ll * ans * i % mod * invs[tsize[i]] % mod;
        printf("%d\n", ans);
    }
    return 0;
}