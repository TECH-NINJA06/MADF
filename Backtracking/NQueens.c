#include <stdio.h>
#include <stdlib.h>

#define N 4

int x[N];

int Place(int k, int i) {
    for (int j = 0; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
            return 0;
        }
    }
    return 1;
}

void PrintBoard() {
    char board[N][N];
    for (int i = 0; i<N ; i++) {
        for (int j = 0; j<N; j++) {
            board[i][j] = '.';
        }
    }

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

void NQueens(int k, int n) {
    for (int i = 0; i < n; i++) {
        if (Place(k, i)) {
            x[k] = i;
            if (k == n - 1) {
                PrintBoard();
            } else {
                NQueens(k + 1, n);
            }
        }
    }
}

int main() {
    NQueens(0, N);
    return 0;
}