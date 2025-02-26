#include <stdio.h>
#include <limits.h>

#define MAX_N 100

int n;
double A[MAX_N][MAX_N], cost[MAX_N][MAX_N];
int path[MAX_N][MAX_N]; 

void printMatrix(int k) {
    printf("\nAfter using vertex %d as intermediate:\n", k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%.0f ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nPath matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", path[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void printPath(int i, int j) {
    if (i == j) {
        printf("%d", i);
        return;
    }
    if (path[i][j] == -1) {
        printf("No path exists");
        return;
    }
    printf("%d -> ", i);
    printPath(path[i][j], j);
}

void AllPaths(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = cost[i][j];
            if (i != j && cost[i][j] != INT_MAX) {
                path[i][j] = j;  
            } else {
                path[i][j] = -1;
            }
        }
    }
    
    printf("\nInitial matrices:");
    printMatrix(-1);
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][k] != INT_MAX && A[k][j] != INT_MAX) {
                    if (A[i][j] > A[i][k] + A[k][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                        path[i][j] = path[i][k]; 
                    }
                }
            }
        }
        printMatrix(k);
    }
}

int main() {
    n = 4; 
    
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            cost[i][j] = (i == j) ? 0 : INT_MAX;
        }
    }
    
    cost[0][1] = 3; cost[0][2] = 8; cost[2][1] = 4;
    cost[4][0] = 2; cost[1][3] = 1;
    cost[0][4] = -4; cost[3][2] = -5;
    cost[4][3] = 6; cost[1][4] = 7;
    
    AllPaths(n);
    
    printf("\nFinal shortest path matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%.0f ", A[i][j]);
        }
        printf("\n");
    }
    
    printf("\nPaths between all pairs of vertices:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && A[i][j] != INT_MAX) {
                printf("Path from %d to %d: ", i, j);
                printPath(i, j);
                printf(" (Cost: %.0f)\n", A[i][j]);
            }
        }
    }
    
    return 0;
}
