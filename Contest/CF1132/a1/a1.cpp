#include <cstdio>
#include <stdio.h>

int T;
int n;

int main() {
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        int a = n >> 1, b = n - a;
        printf("%d\n", a * b);
    }
    return 0;
}