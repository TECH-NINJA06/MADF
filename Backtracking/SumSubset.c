#include <stdio.h>
#include <stdlib.h>

int n, m;
int w[100], x[100];
int nodes = 1;

void SumOfSub(int s, int k, int r) {
    if (k >= n)
        return;

    x[k] = 1;
    if (s + w[k] + w[k + 1] <= m) {
        SumOfSub(s + w[k], k + 1, r - w[k]);
    }

    if (s + r - w[k] >= m && s + w[k + 1] <= m) {
        x[k] = 0;
        SumOfSub(s, k + 1, r - w[k]);
    }
    if (s + w[k] == m) {
        printf("Solution found: ");
        for (int i = 0; i <= k; i++) {
            printf("x%d = %d ", i + 1, x[i]);
        }
        printf("\n");
    }
}

int main() {
    int r = 0;
    printf("Enter size of set: ");
    scanf("%d", &n);
    printf("Enter sum: ");
    scanf("%d", &m);
    printf("Enter elements of set: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        r += w[i];
    }

    SumOfSub(0, 0, r);

    return 0;
}