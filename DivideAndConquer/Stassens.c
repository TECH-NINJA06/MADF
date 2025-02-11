#include <stdio.h>
#include <stdlib.h>

// Check if number is power of 2
int isPowerOfTwo(int n) {
    return (n != 0) && ((n & (n - 1)) == 0);
}

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
    
    // Dynamically allocate memory for all matrices
    int **A11 = malloc(half * sizeof(int*));
    int **A12 = malloc(half * sizeof(int*));
    int **A21 = malloc(half * sizeof(int*));
    int **A22 = malloc(half * sizeof(int*));
    int **B11 = malloc(half * sizeof(int*));
    int **B12 = malloc(half * sizeof(int*));
    int **B21 = malloc(half * sizeof(int*));
    int **B22 = malloc(half * sizeof(int*));
    int **P = malloc(half * sizeof(int*));
    int **Q = malloc(half * sizeof(int*));
    int **R = malloc(half * sizeof(int*));
    int **S = malloc(half * sizeof(int*));
    int **T = malloc(half * sizeof(int*));
    int **U = malloc(half * sizeof(int*));
    int **V = malloc(half * sizeof(int*));
    int **temp1 = malloc(half * sizeof(int*));
    int **temp2 = malloc(half * sizeof(int*));
    int **subC = malloc(half * sizeof(int*));

    for(int i = 0; i < half; i++) {
        A11[i] = malloc(half * sizeof(int));
        A12[i] = malloc(half * sizeof(int));
        A21[i] = malloc(half * sizeof(int));
        A22[i] = malloc(half * sizeof(int));
        B11[i] = malloc(half * sizeof(int));
        B12[i] = malloc(half * sizeof(int));
        B21[i] = malloc(half * sizeof(int));
        B22[i] = malloc(half * sizeof(int));
        P[i] = malloc(half * sizeof(int));
        Q[i] = malloc(half * sizeof(int));
        R[i] = malloc(half * sizeof(int));
        S[i] = malloc(half * sizeof(int));
        T[i] = malloc(half * sizeof(int));
        U[i] = malloc(half * sizeof(int));
        V[i] = malloc(half * sizeof(int));
        temp1[i] = malloc(half * sizeof(int));
        temp2[i] = malloc(half * sizeof(int));
        subC[i] = malloc(half * sizeof(int));
    }

    // Divide matrices into 4 sub-matrices each
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

    // P = (A11 + A22)(B11 + B22)
    addMatrices(half, A11, A22, temp1);
    addMatrices(half, B11, B22, temp2);
    strassen(half, temp1, temp2, P);

    // Q = (A21 + A22)B11
    addMatrices(half, A21, A22, temp1);
    strassen(half, temp1, B11, Q);

    // R = A11(B12 - B22)
    subtractMatrices(half, B12, B22, temp1);
    strassen(half, A11, temp1, R);

    // S = A22(B21 - B11)
    subtractMatrices(half, B21, B11, temp1);
    strassen(half, A22, temp1, S);

    // T = (A11 + A12)B22
    addMatrices(half, A11, A12, temp1);
    strassen(half, temp1, B22, T);

    // U = (A21 - A11)(B11 + B12)
    subtractMatrices(half, A21, A11, temp1);
    addMatrices(half, B11, B12, temp2);
    strassen(half, temp1, temp2, U);

    // V = (A12 - A22)(B21 + B22)
    subtractMatrices(half, A12, A22, temp1);
    addMatrices(half, B21, B22, temp2);
    strassen(half, temp1, temp2, V);

    // Calculate C11, C12, C21, C22
    // C11 = P + S - T + V
    addMatrices(half, P, S, temp1);
    subtractMatrices(half, temp1, T, temp2);
    addMatrices(half, temp2, V, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j] = subC[i][j];
        }
    }

    // C12 = R + T
    addMatrices(half, R, T, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i][j + half] = subC[i][j];
        }
    }

    // C21 = Q + S
    addMatrices(half, Q, S, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {
            C[i + half][j] = subC[i][j];
        }
    }

    // C22 = P - Q + R + U
    subtractMatrices(half, P, Q, temp1);
    addMatrices(half, temp1, R, temp2);
    addMatrices(half, temp2, U, subC);
    for (int i = 0; i < half; i++) {
        for (int j = 0; j < half; j++) {

            C[i + half][j + half] = subC[i][j];
        }
    }

    // Free allocated memory
    for(int i = 0; i < half; i++) {
        free(A11[i]); free(A12[i]); free(A21[i]); free(A22[i]);
        free(B11[i]); free(B12[i]); free(B21[i]); free(B22[i]);
        free(P[i]); free(Q[i]); free(R[i]); free(S[i]);
        free(T[i]); free(U[i]); free(V[i]);
        free(temp1[i]); free(temp2[i]); free(subC[i]);
    }
    free(A11); free(A12); free(A21); free(A22);
    free(B11); free(B12); free(B21); free(B22);
    free(P); free(Q); free(R); free(S);
    free(T); free(U); free(V);
    free(temp1); free(temp2); free(subC);
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
    int n;
    printf("Enter matrix size (must be a power of 2): ");
    scanf("%d", &n);

    if (!isPowerOfTwo(n)) {
        printf("Matrix size must be a power of 2\n");
        return 1;
    }

    int A[n][n], B[n][n], C[n][n] = {0};

    printf("Enter elements of first matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &A[i][j]);

    printf("Enter elements of second matrix:\n");
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            scanf("%d", &B[i][j]);

    strassen(n, A, B, C);

    printf("Resultant matrix C:\n");
    printMatrix(n, C);

    return 0;
}
