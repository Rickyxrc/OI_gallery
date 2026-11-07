#include <algorithm>
#include <cstdio>
#include <stdio.h>
#include <utility>

typedef long long i64;

i64 mod;

struct matrix {
    i64 dat[2][2] = {{0, 0}, {0, 0}};
} I;

inline matrix operator*(const matrix &a, const matrix &b) {
    matrix s;
    s.dat[0][0] =
        (i64(a.dat[0][0]) * b.dat[0][0] + i64(a.dat[0][1]) * b.dat[1][0]) % mod;
    s.dat[0][1] =
        (i64(a.dat[0][0]) * b.dat[0][1] + i64(a.dat[0][1]) * b.dat[1][1]) % mod;
    s.dat[1][0] =
        (i64(a.dat[1][0]) * b.dat[0][0] + i64(a.dat[1][1]) * b.dat[1][0]) % mod;
    s.dat[1][1] =
        (i64(a.dat[1][0]) * b.dat[0][1] + i64(a.dat[1][1]) * b.dat[1][1]) % mod;
    return s;
}

inline matrix transition(int si_1, int si_2) {
    matrix r;
    r.dat[0][0] = si_1, r.dat[0][1] = si_2;
    r.dat[1][0] = 1, r.dat[1][1] = 0;
    return r;
}

i64 k;
#define maxn 50007
#define maxh 63
int li[maxn], n, m, moded;
i64 u;
int v;
std::pair<i64, int> dif[maxn];

matrix qm[maxn][maxh];

int main() {
    I.dat[0][0] = I.dat[1][1] = 1;

    scanf("%lld%lld", &k, &mod);
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", li + i);

    for (int i = 0; i < n; i++) {
        int tind = i % n, tindp1 = (i + n - 1) % n;
        qm[i][0] = transition(li[tind], li[tindp1]);
    }

    for (int j = 1; j < maxh; j++)
        for (int i = 0; i < n; i++) {
            int gp = (i + (1ll << (j - 1))) % n;
            qm[i][j] = qm[gp][j - 1] * qm[i][j - 1];
        }

    scanf("%d", &m);
    for (int i = 1; i <= m; i++)
        scanf("%lld%d", &dif[i].first, &dif[i].second);
    dif[++m] = {k, li[k % n]};
    std::sort(dif + 1, dif + m + 1);

    i64 stat = 1;
    int p = 1;

    if (k == 0 or mod == 1) {
        puts("0");
        return 0;
    }

    matrix r;
    r.dat[0][0] = 1;

    while (stat != k) {
        int index = stat % n;
        int indexp1 = (index + n - 1) % n;

        moded = 0;
        int si_1 = li[index];
        if (stat == dif[p].first)
            moded = 1, si_1 = dif[p].second;

        int si_2 = li[indexp1];
        if (stat == dif[p - 1].first + 1)
            moded = 1, si_2 = dif[p - 1].second;

        if (moded) {
            matrix T = transition(si_1, si_2);

            r = T * r;
            if (stat == dif[p].first)
                p++;

            stat++;
        } else {
            for (int l = maxh - 1; l >= 0; l--)
                if (stat + (1ll << l) < dif[p].first)
                    r = qm[stat % n][l] * r, stat += (1ll << l);

            if (stat != dif[p].first)
                r = qm[stat % n][0] * r, stat++;
        }
    }

    printf("%lld", r.dat[0][0]);

    return 0;
}