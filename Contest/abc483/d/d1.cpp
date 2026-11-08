#include <algorithm>
#include <stdio.h>

#define maxn 2000007
typedef long long i64;

struct node {
    i64 mx, mn, lazy;
    node(i64 mx = 0, i64 mn = 0, i64 lazy = 0) : mx(mx), mn(mn), lazy(lazy) {}
} tree[maxn];

#define call int mid = (l + r) >> 1, ls = index << 1, rs = ls | 1;

inline i64 min(i64 a, i64 b) { return a < b ? a : b; }
inline i64 max(i64 a, i64 b) { return a > b ? a : b; }

void upd(int index, int l, int r) {
    call;
    tree[index].mx = max(tree[ls].mx, tree[rs].mx);
    tree[index].mn = min(tree[ls].mn, tree[rs].mn);
}

i64 li[maxn], s[maxn];
void init(int index, int l, int r) {
    if (l == r) {
        if (l != 1)
            scanf("%lld", li + l);
        s[l] = li[l] + s[l - 1];
        tree[index].mx = tree[index].mn = s[l];
        return;
    }
    call;
    init(ls, l, mid), init(rs, mid + 1, r);
    upd(index, l, r);
}

void pushlazy(int index, int l, int r) {
    call;
    i64 v = tree[index].lazy;
    tree[index].lazy = 0;

    tree[ls].lazy += v;
    tree[ls].mn += v;
    tree[ls].mx += v;

    tree[rs].lazy += v;
    tree[rs].mn += v;
    tree[rs].mx += v;
}

void add(int index, int l, int r, int ql, int qr, i64 v) {
    pushlazy(index, l, r);
    if (ql <= l and r <= qr) {
        tree[index].lazy += v;
        tree[index].mn += v;
        tree[index].mx += v;
        return;
    }
    if (l > qr or r < ql)
        return;
    call;

    add(ls, l, mid, ql, qr, v);
    add(rs, mid + 1, r, ql, qr, v);
    upd(index, l, r);
}

typedef std::pair<i64, i64> pi6;

pi6 qminmx(int index, int l, int r, int ql, int qr) {
    pushlazy(index, l, r);
    if (ql <= l and r <= qr)
        return {tree[index].mn, tree[index].mx};
    if (l > qr or r < ql)
        return {1ll << 62, -(1ll << 62)};
    call;

    auto lv = qminmx(ls, l, mid, ql, qr), rv = qminmx(rs, mid + 1, r, ql, qr);
    return {min(lv.first, rv.first), max(lv.second, rv.second)};
}

int n;
i64 ans;
int main() {
    scanf("%d", &n);
    n++;
    init(1, 1, n);

    auto r = qminmx(1, 1, n, 1, n);
    ans = r.second - r.first;

    for (int i = 2; i <= n; i++) {

        add(1, 1, n, i, n, -2 * li[i]);

        auto r = qminmx(1, 1, n, 1, n);
        ans = max(ans, r.second - r.first);

        add(1, 1, n, i, n, 2 * li[i]);
    }

    printf("%lld\n", ans + 1);

    return 0;
}