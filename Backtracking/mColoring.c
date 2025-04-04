#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100

int x[MAX], n,M;
int m[MAX][MAX];

void NextValue(int k) {
    while (1) {
        x[k] = (x[k] + 1) % (M + 1);
        if (x[k] == 0) return;
        int j;
        for (j = 0; j < n; j++)
            if (x[k] == x[j] && m[k][j] == 1 && k != j) break;
        if (j == n) return;
    }
}

void mColoring(int k) {
    while (1) {
        NextValue(k);
        if (x[k] == 0) return;
        if (k == n - 1) {
            
            for (int i = 0; i < n; i++) {
                printf("%2d ", x[i]);
            }
            printf("\n");
        } else
            mColoring(k + 1);
    }
}

int main() {
    M=2;
    clock_t start, end;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &m[i][j]);
    printf("\nSolution Vector:\n");
    for(int i=0;i<n;i++)
        printf("[%d]",i+1);
    printf("\n");
    for (int i = 0; i < n; i++)
        x[i] = 0;
    start = clock(); 
    mColoring(0);
    end = clock(); 
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;
    printf("Execution time: %.2f ms\n", time_taken);

    return 0;
}