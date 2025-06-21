#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Place(int x[], int k, int i) {
    for (int j = 0; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return 0;
        }
    }
    return 1;
}

void PrintBoard(int x[], int N) {
    char board[N][N];
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = '-';
        }
    }
    printf("Solution vector x: ");
    for (int i = 0; i < N; i++) {
        printf("%d ", x[i]+1);
    }
    printf("\n");
    for (int i = 0; i < N; i++) {
        board[i][x[i]] = 'Q';
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int NQueens(int x[], int k, int n, int *solutionCount, int *firstSolutionPrinted) {
    for (int i = 0; i < n; i++) {
        if (Place(x, k, i)) {
            x[k] = i;
            if (k == n - 1) {
                (*solutionCount)++;
                if (!(*firstSolutionPrinted)) {
                    printf("First solution for N = %d:\n", n);
                    PrintBoard(x, n);
                    *firstSolutionPrinted = 1;
                }
            } else {
                NQueens(x, k + 1, n, solutionCount, firstSolutionPrinted);
            }
        }
    }
    return *solutionCount;
}

int main() {
    clock_t start, end;
    double time_ms;
    for (int N = 2; N <= 12; N++) {
        int x[N];
        int solutionCount = 0;
        int firstSolutionPrinted = 0;
        if (N == 4) {
            start = clock();
            solutionCount = NQueens(x, 0, N, &solutionCount, &firstSolutionPrinted);
            end = clock();
        }
        solutionCount = NQueens(x, 0, N, &solutionCount, &firstSolutionPrinted);
        printf("N = %d, Number of solutions: %d\n", N, solutionCount);
        printf("-----------------------------\n");
    }
    time_ms = ((double)(end - start)) * 1000.0 / CLOCKS_PER_SEC;
    printf("\nExecution time: %.6f ms\n", time_ms);
    return 0;
}