#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100

int n, m, w[MAX], p[MAX], x[MAX], y[MAX], fp, fw;

float Bound(int cp, int cw, int k) {
    float b = cp;
    int c = cw;
    for (int i = k + 1; i < n; i++) {
        c = c + w[i];
        if (c < m)
            b = b + p[i];
        else
            return b + (1 - (c - m) / (float)w[i]) * p[i];
    }
    return b;
}

void BKnap(int k, int cp, int cw) {
    if (cw + w[k] <= m) {
        y[k] = 1;
        if (k < n - 1)
            BKnap(k + 1, cp + p[k], cw + w[k]);
        if ((cp + p[k] > fp) && (k == n - 1)) {
            fp = cp + p[k];
            fw = cw + w[k];
            for (int i = 0; i < n; i++) {
                x[i] = y[i];
            }
        }
    }
    if (Bound(cp, cw, k) >= fp) {
        y[k] = 0;
        if (k < n - 1)
            BKnap(k + 1, cp, cw);
        if ((cp > fp) && (k == n - 1)) {
            fp = cp;
            fw = cw;
            for (int i = 0; i < n; i++) {
                x[i] = y[i];
            }
        }
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    printf("Enter the number of items: ");
    scanf("%d", &n);
    printf("Enter the capacity of the knapsack: ");
    scanf("%d", &m);

    printf("Enter the weights of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    printf("Enter the profits of the items:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    fp = 0;
    fw = 0;

    start = clock(); // Start the timer
    BKnap(0, 0, 0);
    end = clock(); // End the timer

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC * 1000; // Convert to milliseconds

    printf("Maximum profit: %d\n", fp);
    printf("Weights included in the knapsack:\n");
    for (int i = 0; i < n; i++) {
        if (x[i]) {
            printf("Item %d (Weight: %d, Profit: %d)\n", i + 1, w[i], p[i]);
        }
    }

    printf("Execution time: %.2f ms\n", cpu_time_used);

    return 0;
}