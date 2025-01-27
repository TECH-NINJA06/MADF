#include <stdio.h>
#include <stdlib.h>

void addMatrices(int n, int A[n][n], int B[n][n], int result[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtractMatrices(int n, int A[n][n], int B[n][n], int result[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int half = n / 2;
    int subA[half][half], subB[half][half], subC[half][half];
    int M1[half][half], M2[half][half], M3[half][half], M4[half][half];
    int M5[half][half], M6[half][half], M7[half][half];
    int temp1[half][half], temp2[half][half];

    int A11[half][half], A12[half][half], A21[half][half], A22[half][half];
    int B11[half][half], B12[half][half], B21[half][half], B22[half][half];

    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + half];
            A21[i][j] = A[i + half][j];
            A22[i][j] = A[i + half][j + half];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + half];
            B21[i][j] = B[i + half][j];
            B22[i][j] = B[i + half][j + half];
        }
    }

    // P = (A11 + A22) * (B11 + B22)
    addMatrices(half, A11, A22, temp1);
    addMatrices(half, B11, B22, temp2);
    strassen(half, temp1, temp2, M1);

    // Q = (A21 + A22) * B11
    addMatrices(half, A21, A22, temp1);
    strassen(half, temp1, B11, M2);

    // R = A11 * (B12 - B22)
    subtractMatrices(half, B12, B22, temp1);
    strassen(half, A11, temp1, M3);

    // S = A22 * (B21 - B11)
    subtractMatrices(half, B21, B11, temp1);
    strassen(half, A22, temp1, M4);

    // T = (A11 + A12) * B22
    addMatrices(half, A11, A12, temp1);
    strassen(half, temp1, B22, M5);

    // U = (A21 - A11) * (B11 + B12)
    subtractMatrices(half, A21, A11, temp1);
    addMatrices(half, B11, B12, temp2);
    strassen(half, temp1, temp2, M6);

    // V = (A12 - A22) * (B21 + B22)
    subtractMatrices(half, A12, A22, temp1);
    addMatrices(half, B21, B22, temp2);
    strassen(half, temp1, temp2, M7);

    // C11 = M1 + M4 - M5 + M7
    addMatrices(half, M1, M4, temp1);
    subtractMatrices(half, temp1, M5, temp2);
    addMatrices(half, temp2, M7, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = subC[i][j];
        }
    }

    // C12 = M3 + M5
    addMatrices(half, M3, M5, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j + half] = subC[i][j];
        }
    }

    // C21 = M2 + M4
    addMatrices(half, M2, M4, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i + half][j] = subC[i][j];
        }
    }

    // C22 = M1 - M2 + M3 + M6
    subtractMatrices(half, M1, M2, temp1);
    addMatrices(half, temp1, M3, temp2);
    addMatrices(half, temp2, M6, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i + half][j + half] = subC[i][j];
        }
    }
}

void printMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 4; 
    int A[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    int B[4][4] = {
        {17, 18, 19, 20},
        {21, 22, 23, 24},
        {25, 26, 27, 28},
        {29, 30, 31, 32}
    };
    int C[4][4] = {0};

    strassen(n, A, B, C);

    printf("Resultant matrix C:\n");
    printMatrix(n, C);

    return 0;
}