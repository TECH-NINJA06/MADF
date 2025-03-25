#include <stdio.h>

struct Pair {
    float p, w;
    int from;
};

int Largest(struct Pair pair[], int w[], int t, int h, int i, int m) {
    int u = t;
    for (int j = t; j <= h; j++) {
        if (pair[j].w + w[i] <= m) {
            u = j;
        }
    }
    return u;
}

void TraceBack(struct Pair pair[], int p[], int w[], int x[], int n, int b[]) {
    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    int max_idx = 0;
    float max_profit = 0;
    for (int i = b[n]; i < b[n + 1]; i++) {
        if (pair[i].p > max_profit) {
            max_profit = pair[i].p;
            max_idx = i;
        }
    }

    for (int i = n; i >= 1; i--) {
        int predecessor = pair[max_idx].from;
        if (predecessor != -1) {
            if (pair[max_idx].w != pair[predecessor].w) {
                x[i - 1] = 1;
            }
        }
        max_idx = predecessor;
    }

    printf("Solution vector x: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    float total_profit = 0, total_weight = 0;
    for (int i = 0; i < n; i++) {
        if (x[i] == 1) {
            total_profit += p[i];
            total_weight += w[i];
        }
    }
    printf("Total profit: %.0f\n", total_profit);
    printf("Total weight: %.0f\n", total_weight);
}

void DKnap(int p[], int x[], int w[], int n, int m) {
    struct Pair pair[1000];
    int b[1000];
    int t = 1, h = 1, next = 2;

    pair[1].p = pair[1].w = 0.0;
    pair[1].from = -1;
    b[0] = 1;
    b[1] = next;

    printf("\nS^0 = { (0,0) }");

    for (int i = 1; i <= n; i++) {
        int k = t;
        int u = Largest(pair, w, t, h, i - 1, m);
        printf("\nS^%d = {", i);

        for (int j = t; j <= u; j++) {
            float pp = pair[j].p + p[i - 1];
            float ww = pair[j].w + w[i - 1];

            while ((k <= h) && (pair[k].w <= ww)) {
                printf(" (%.0f,%.0f),", pair[k].p, pair[k].w);
                pair[next] = pair[k];
                next++;
                k++;
            }

            if ((k <= h) && (pair[k].w == ww)) {
                if (pp < pair[k].p)
                    pp = pair[k].p;
                k++;
            }

            if (pp > pair[next - 1].p) {
                printf(" (%.0f,%.0f),", pp, ww);
                pair[next].p = pp;
                pair[next].w = ww;
                pair[next].from = j;
                next++;
            }

            while ((k <= h) && (pair[k].p <= pair[next - 1].p)) {
                k++;
            }
        }

        while (k <= h) {
            printf(" (%.0f,%.0f),", pair[k].p, pair[k].w);
            pair[next] = pair[k];
            next++;
            k++;
        }

        printf("\b }");
        t = h + 1;
        h = next - 1;
        b[i + 1] = next;
    }

    printf("\n");

    TraceBack(pair, p, w, x, n, b);
}

int main() {
    int n, m;
    printf("Enter n: ");
    scanf("%d", &n);
    printf("Enter m: ");
    scanf("%d", &m);

    int p[n], w[n], x[n];

    printf("Enter profits:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("Enter weights:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    DKnap(p, x, w, n, m);

    return 0;
}
