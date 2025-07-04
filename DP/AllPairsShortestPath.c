#include <stdio.h>
#include <time.h>
#include <limits.h>

#define MAX_N 100

int n = 5;
int A[MAX_N][MAX_N], cost[MAX_N][MAX_N];
int path[MAX_N][MAX_N]; 

void printMatrix(int k) {
    printf("\nA^%d\n", k+1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (A[i][j] == INT_MAX)
                printf("INF ");
            else
                printf("%3d ", A[i][j]);
        }
        
        printf("\n");
    }
    
    printf("\nP^%d:\n", k+1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (path[i][j] == -1)
                printf("  - ");
            else printf("%3d ", path[i][j] + 1);
        }
        printf("\n");
    }
    printf("\n");
}

void printPath(int i, int j) {
    if (i == j) {
        printf("%d", i + 1);
        return;
    }
    if (path[i][j] == -1) {
        printf(" No path ");
        return;
    }
    printPath(i, path[i][j]);
    printf(" -> %d", j + 1);
}


void AllPaths(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = cost[i][j];
            if (i != j) {
                path[i][j] = i;
            } else {
                path[i][j] = -1;
            }
        }
    }
    printMatrix(-1);
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (A[i][k] != INT_MAX && A[k][j] != INT_MAX) {
                    if (A[i][j] > A[i][k] + A[k][j]) {
                        A[i][j] = A[i][k] + A[k][j];
                        path[i][j] = path[k][j];
                    }
                }
            }
        }
        printMatrix(k);
    }
}

int main() {
    clock_t start, end; 
    double time_taken;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                cost[i][i] = 0;
            else
                cost[i][j] = INT_MAX;
        }
    }

    cost[0][1] = -2; cost[0][2] = -4; cost[0][3] = 3; cost[0][4] = -1;
    cost[1][0] = 3; cost[1][2] = 2; cost[1][3] = 2; cost[1][4] = 4;
    cost[2][0] = 6; cost[2][1] = 2; cost[2][3] = 2; cost[2][4] = 4;
    cost[3][0] = 3; cost[3][1] = 2; cost[3][2] = 2; cost[3][4] = 3;
    cost[4][0] = 5; cost[4][1] = 4; cost[4][2] = -3; cost[4][3] = 3;

    start = clock();
    AllPaths(n);
    end = clock();
    time_taken = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;
    printf("Source\tDestination\tLength\tPath\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j && A[i][j] != INT_MAX) {
                printf("%d\t    %d\t", i+1, j+1);
                printf("\t%d\t", A[i][j]);
                printPath(i, j);
                printf("\n");
            }
        }
    }

    printf("\n");
    printf("\nExecution Time: %.6f ms\n", time_taken);

    return 0;
}
