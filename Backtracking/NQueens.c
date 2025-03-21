#include <stdio.h>
#include <stdlib.h>

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

void NQueens(int x[], int k, int n) {
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
    int N;
    printf("Enter the number of queens: ");
    scanf("%d", &N);
    int x[N];
    NQueens(0, N);
    return 0;
}