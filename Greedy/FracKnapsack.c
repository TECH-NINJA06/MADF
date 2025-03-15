#include <stdio.h>

int n;
int p[100], w[100];

void printSolutionVector(float x[]) {
    printf("\nSolution Vector: ");
    for (int i = 0; i < n; i++) {
        if (x[i] == 1.0)
            printf("X%d + ", i + 1);
        else if (x[i] > 0)
            printf("%.2fX%d + ", x[i], i + 1);
    }
    printf("\b\b \n");
}

void knapsack(int n, int m, int mode) {
    float x[n], ratio[n];
    int remaining = m, index[n];
    float totalProfit = 0;

    for (int i = 0; i < n; i++) {
        index[i] = i;
        x[i] = 0.0;
        ratio[i] = (float)p[i] / w[i];
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int swap = 0;
            if (mode == 1 && w[index[j]] > w[index[j + 1]]) 
                swap = 1;
            if (mode == 2 && p[index[j]] < p[index[j + 1]]) 
                swap = 1;
            if (mode == 3 && ratio[index[j]] < ratio[index[j + 1]]) 
                swap = 1;

            if (swap) {
                int temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
    }

    printf("\nWeights (w): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", w[index[i]]);
    }

    printf("\nProfits (p): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", p[index[i]]);
    }

    printf("\nFraction (f): ");
    for (int i = 0; i < n && remaining > 0; i++) {
        int id = index[i];

        if (w[id] <= remaining) {
            x[id] = 1.0;
            remaining -= w[id];
            totalProfit += p[id];
        } else {
            x[id] = (float)remaining / w[id];
            totalProfit += x[id] * p[id];
            remaining = 0;
        }
        printf("%.2f ", x[id]);
    }

    printf("\nSum wixi = %d", m);
    printf("\nSum pixi = %.2f", totalProfit);

    printSolutionVector(x);
}

int main() {
    int m;

    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    printf("Enter weights (w1, w2, ...): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }

    printf("Enter value of m (capacity): ");
    scanf("%d", &m);

    printf("Enter profits (p1, p2, ...): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
    }

    printf("\nUsing Maximum Profit");
    knapsack(n, m, 2);

    printf("\nUsing Least Weight");
    knapsack(n, m, 1);

    printf("\nUsing Maximum Profit/Weight Ratio");
    knapsack(n, m, 3);

    return 0;
}
