#include <stdio.h>
#include <vector>
#define maxn 200007

using namespace std;

vector<int> edge[maxn], ans[maxn];
int req[maxn], mk[maxn], vis[maxn];
int n, m, u, v, tp;

int sol = 1;
void dfs(int index, int fa) {
    if (not sol or vis[index])
        return;
    mk[index] = 1;
    vis[index] = 1;

    for (auto v : edge[index]) {
        if (v != fa) {
            if (req[v] == req[index] + 1) {
                ans[index].push_back(v);
                dfs(v, index);
            }
        }
    }

    for (auto v : edge[index]) {
        if (v != fa and req[v] != req[index] + 1) {
            ans[index].push_back(v);
            if (req[v] <= req[index]) {
                if (not mk[v]) {
                    sol = 0;
                    return;
                }
            }
        }
    }

    if (fa)
        ans[index].push_back(fa);

    mk[index] = 0;
}

int st;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", req + i);
        if (req[i] == 0) {
            if (st) {
                printf("-1");
                return 0;
            } else {
                st = i;
            }
        }
    }

    if (not st) {
        printf("-1");
        return 0;
    }

    for (int u = 1; u <= n; u++) {
        scanf("%d", &tp);
        for (int i = 1; i <= tp; i++)
            scanf("%d", &v),
                //  printf("Edge: %d <-> %d\n", u, v),
                edge[u].push_back(v);
    }

    dfs(st, 0);

    if (not sol) {
        printf("-1");
        return 0;
    }

    for (int i = 1; i <= n; i++)
        if (not vis[i]) {
            printf("-1");
            return 0;
        }

    printf("%d\n", st);

    for (int u = 1; u <= n; u++) {
        for (auto v : ans[u])
            printf("%d ", v);
        puts("");
    }

    return 0;
}