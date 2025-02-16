#include <stdio.h>
#include <limits.h>

#define MAX_N 100

int n;
double A[MAX_N][MAX_N], cost[MAX_N][MAX_N];

void AllPaths(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = cost[i][j];
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][k] != INT_MAX && A[k][j] != INT_MAX) {
                    if (A[i][j] > A[i][k] + A[k][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                    }
                }
            }
        }
    }
}

int main() {
    n = 4; 
    
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    
    cost[0][1] = 3; cost[0][2] = 10;
    cost[1][2] = 2; cost[1][3] = 6;
    cost[2][3] = 1;
    
    AllPaths(n);
    
    printf("Shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%.0f ", A[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
