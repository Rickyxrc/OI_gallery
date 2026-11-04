#include <stdio.h>
#include <vector>

#define maxn 2000007

std::vector<int> vers[maxn], invs[maxn];

int fas[maxn], n, m;
int cnt;
int vU, vT, vF;
void init() {
    for (int i = 1; i < maxn; i++)
        vers[i].clear(), invs[i].clear(), fas[i] = i;
    cnt = 0;
    vU = ++cnt;
    vT = ++cnt;
    vF = ++cnt;
}

int ffa(int x) {
    if (fas[x] == x)
        return x;
    return fas[x] = ffa(fas[x]);
}

inline void merge(int u, int v) { fas[ffa(u)] = fas[ffa(v)]; }
inline int check(int u, int v) { return ffa(u) == ffa(v); }

char gc() {
    char c = ' ';
    do {
        c = getchar();
    } while (c != '+' and c != '-' and c != 'T' and c != 'F' and c != 'U');
    return c;
}

// last version of x
inline int gp(int x) { return *(--vers[x].end()); }
inline int gpinv(int x) { return *(--invs[x].end()); }
// insert new version of x
inline int np(int x) {
    vers[x].push_back(++cnt);
    return gp(x);
}
inline int npinv(int x) {
    invs[x].push_back(++cnt);
    return gpinv(x);
}
// first version of x
inline int gf(int x) { return (vers[x][0]); }
inline int gfinv(int x) { return (invs[x][0]); }

int _, T, u, v;
char op;

int main() {
    scanf("%d%d", &_, &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        init();
        for (int i = 1; i <= n; i++)
            np(i), npinv(i);
        // puts("");

        for (int i = 1; i <= m; i++) {
            op = gc();
            if (op == 'T') {
                scanf("%d", &u);

                merge(np(u), vT);
                merge(npinv(u), vF);
            }
            if (op == 'F') {
                scanf("%d", &u);

                merge(np(u), vF);
                merge(npinv(u), vT);
            }
            if (op == 'U') {
                scanf("%d", &u);

                merge(np(u), vU);
                merge(npinv(u), vU);
            }

            if (op == '+') {
                scanf("%d%d", &u, &v);

                int p = gp(v), pi = gpinv(v);
                merge(np(u), p);
                merge(npinv(u), pi);
            }
            if (op == '-') {
                scanf("%d%d", &u, &v);

                int p = gp(v), pi = gpinv(v);
                merge(np(u), pi);
                merge(npinv(u), p);
            }
        }

        int ans = 0;

        for (int i = 1; i <= n; i++)
            merge(gp(i), gf(i)), merge(gpinv(i), gfinv(i));

        for (int i = 1; i <= n; i++)
            if (check(gp(i), gfinv(i)))
                merge(gp(i), vU), merge(gpinv(i), vU);

        for (int i = 1; i <= n; i++) {
            if (check(gp(i), vU))
                ans++;
        }

        printf("%d\n", ans);
    }
    return 0;
}