#include <algorithm>
#include <stdio.h>

#define maxn 200007

typedef long long i64;

struct s {
  int x, y;
} li[maxn];

bool cmp(const s &a, const s &b) {
  if (a.x == 0)
    return true;
  if (b.x == 0)
    return false;

  // a.y/a.x - b.y/b.x < 0;
  // ay bx - ax by < 0 ()rev if ax bx < 0
  i64 r = 1ll * a.y * b.x - 1ll * a.x * b.y;

  if (1ll * a.x * b.x > 0)
    return r < 0;
  else
    return r > 0;
}

int liner = 0, mx;

int T, n;

inline int max(int a, int b) { return a > b ? a : b; }

int main() {
  scanf("%d", &T);

  while (T--) {
    liner = 0;
    mx = -1;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d", &li[i].x, &li[i].y);

      if (li[i].x == 0)
        liner += (li[i].y > 0);
      else
        liner += (li[i].x > 0);
    }
    mx = max(mx, max(liner, n - liner));

    std::sort(li + 1, li + n + 1, cmp);

    for (int i = 1; i <= n; i++) {
      //   printf("(%d, %d) slope = %lf\n", li[i].x, li[i].y,
      //  1. * li[i].y / li[i].x);

      if (li[i].x > 0) {
        liner--;
      }

      if (li[i].x < 0) {
        liner++;
      }

      mx = max(mx, max(liner, n - liner));
    }

    printf("%d\n", mx);
  }
  return 0;
}