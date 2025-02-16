#include <stdio.h>
#include <limits.h>

#define MAX_N 100 

int n, k;
double cost[MAX_N];
int d[MAX_N], p[MAX_N];
double c[MAX_N][MAX_N];

void FGraph(int n, int k) {
    cost[n] = 0.0; 
    for (int j = n - 1; j >= 1; j--) {
        int r = -1;
        double minCost = INT_MAX;
        
        // Find minimum cost edge from j
        for (int i = j + 1; i <= n; i++) {
            if (c[j][i] > 0 && c[j][i] + cost[i] < minCost) {
                minCost = c[j][i] + cost[i];
                r = i;
            }
        }
        
        cost[j] = minCost;
        d[j] = r;
    }
    
    // Find the minimum-cost path
    p[1] = 1;
    p[k] = n;
    for (int j = 2; j <= k - 1; j++) {
        p[j] = d[p[j - 1]];
    }
}

void BGraph(int n, int k) {
    cost[1] = 0.0;
    for (int j = 2; j <= k; j++) {
        int r = -1;
        double minCost = INT_MAX;
        for (int i = j - 1; i >= 1; i--) {
            if (c[i][j] > 0 && cost[i] + c[i][j] < minCost) {
                minCost = cost[i] + c[i][j];
                r = i;
            }
        }
        cost[j] = minCost;
        p[j] = r;
    }
    p[k] = n;
    for (int j = k - 1; j >= 1; j--) {
        p[j] = d[p[j + 1]];
    }
}

int main() {
    // Example input: 5-stage graph
    n = 6; // Number of vertices
    k = 4; // Number of stages
    
    // Initialize the cost matrix (0 means no edge)
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            c[i][j] = 0;
        }
    }
    
    // Define edges with costs
    c[1][2] = 1; c[1][3] = 2;
    c[2][4] = 4; c[2][5] = 1;
    c[3][4] = 3; c[3][5] = 2;
    c[4][6] = 2; c[5][6] = 3;
    
    // Run the algorithm
    FGraph(n, k);
    
    // Print the minimum cost path
    printf("Minimum-cost path: ");
    for (int i = 1; i <= k; i++) {
        printf("%d ", p[i]);
    }
    printf("\n");
    
    return 0;
}