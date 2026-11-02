#include <map>
#include <stdio.h>
#include <vector>
#define maxn 200007

int li[maxn];
std::vector<int> edge[maxn];
int n, u, v;

int mdp, mdpi;
int fas[maxn], depth[maxn];

void dfs(int index, int fa) {
    depth[index] = depth[fa] + 1;
    fas[index] = fa;
    if (depth[index] > mdp)
        mdp = depth[index], mdpi = index;
    for (auto x : edge[index]) {
        if (x != fa)
            dfs(x, index);
    }
}

typedef long long i64;

i64 ans = 0;
int col[maxn];
int D;

std::map<std::pair<int, int>, int> cts;
std::map<std::pair<int, int>, int> tadd;

void dfs2(int index, int fa) {
    depth[index] = depth[fa] + 1;
    fas[index] = fa;

    for (auto x : edge[index])
        if (x != fa)
            dfs2(x, index);
    ans += cts[{col[index], D - depth[index]}];
    tadd[{col[index], depth[index]}]++;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d%d", &u, &v), edge[u].push_back(v), edge[v].push_back(u);

    mdp = mdpi = 0;
    dfs(1, 0);
    int a1 = mdpi;
    mdp = mdpi = 0;
    dfs(a1, 0);

    D = depth[mdpi] - 1;

    for (int i = 1; i <= n; i++)
        scanf("%d", col + i);

    int cur = mdpi;
    for (int i = 1; i <= (depth[mdpi] - 1) / 2; i++)
        cur = fas[cur];
    depth[cur] = 0;
    cts[{col[cur], 0}]++;
    for (auto x : edge[cur]) {
        dfs2(x, cur);
        for (auto h : tadd) {
            cts[h.first] += h.second;
        }
        tadd.clear();
    }

    printf("%lld", ans);
    return 0;
}