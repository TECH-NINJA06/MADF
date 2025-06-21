#include <stdio.h>
#include <limits.h>

// Function 1: Calculate profit based on user given fractions
void calculateFractionalProfit(float w[], float p[], float f[], int n) {
    float wixi = 0.0, pixi = 0.0;
    for (int i = 1; i <= n; i++) {
        wixi += f[i] * w[i];
        pixi += f[i] * p[i];
    }
    printf("x1    x2    x3    x4    x5    x6    x7    x8    x9    x10    wixi    pixi\n");
    printf("1/2   1/2   1/3   1/3   1/4   1/5   1/6   1/7   1/8   1/9    %.2f   %.2f\n", wixi, pixi);
}

// Function 2: Knapsack based on maximum profits
void knapsackMaxProfit(float w[], float p[], int n, int m) {
    float x[11] = {0};
    float u = m, wixi = 0.0, pixi = 0.0;
    
    for (int i = 1; i <= n; i++) {
        int max = INT_MIN, index = -1;
        for (int j = 1; j <= n; j++) {
            if (p[j] > max && x[j] != 1.0) {
                max = p[j];
                index = j;
            }
        }
        if (w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];
    }
    if (u > 0) 
        x[index] = u / w[index];

    for (int i = 1; i <= n; i++) {
        printf("%.1f   ", x[i]);
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
    printf(" %.2f   %.2f\n", wixi, pixi);
}

// Function 3: Knapsack based on minimum weight
void knapsackMinWeight(float w[], float p[], int n, int m) {
    float x[11] = {0};
    float u = m, wixi = 0.0, pixi = 0.0;

    for (int i = 1; i <= n; i++) {
        int min = INT_MAX, index = -1;
        for (int j = 1; j <= n; j++) {
            if (w[j] < min && x[j] != 1.0) {
                min = w[j];
                index = j;
            }
        }
        if (w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];
    }
    if (u > 0)
        x[index] = u / w[index];

    for (int i = 1; i <= n; i++) {
        printf("%.1f   ", x[i]);
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
    printf(" %.2f   %.2f\n", wixi, pixi);
}

// Function 4: Knapsack based on profit/weight ratio (optimal solution)
void knapsackOptimal(float w[], float p[], int n, int m) {
    float x[11] = {0}, op[11];
    float u = m, wixi = 0.0, pixi = 0.0;

    for (int i = 1; i <= n; i++)
        op[i] = p[i] / w[i];

    for (int i = 1; i <= n; i++) {
        float max = -1;
        int index = -1;
        for (int j = 1; j <= n; j++) {
            if (op[j] > max && x[j] != 1.0) {
                max = op[j];
                index = j;
            }
        }
        if (w[index] > u)
            break;
        x[index] = 1.0;
        u -= w[index];
    }
    if (u > 0)
        x[index] = u / w[index];

    for (int i = 1; i <= n; i++) {
        printf("%.1f   ", x[i]);
        wixi += x[i] * w[i];
        pixi += x[i] * p[i];
    }
    printf(" %.2f   %.2f\n", wixi, pixi);
}

// Main function
int main() {
    int m, n;
    float w[11], p[11];
    float f[11] = {0.0, 0.5, 0.5, 1.0/3, 1.0/3, 0.25, 0.2, 1.0/7, 1.0/8, 1.0/9, 0.11};

    printf("Enter the knapsack capacity: ");
    scanf("%d", &m);
    printf("Enter number of elements in knapsack (max 10): ");
    scanf("%d", &n);

    printf("Enter weights: ");
    for (int i = 1; i <= n; i++)
        scanf("%f", &w[i]);

    printf("Enter profits: ");
    for (int i = 1; i <= n; i++)
        scanf("%f", &p[i]);

    printf("\n--- Based on user fractions ---\n");
    calculateFractionalProfit(w, p, f, n);

    printf("\n--- Based on Maximum Profit ---\n");
    knapsackMaxProfit(w, p, n, m);

    printf("\n--- Based on Minimum Weight ---\n");
    knapsackMinWeight(w, p, n, m);

    printf("\n--- Based on Profit/Weight Ratio (Optimal) ---\n");
    knapsackOptimal(w, p, n, m);

    return 0;
}
