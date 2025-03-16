#include <stdio.h>
#include <time.h>

#define SIZE 4

void addMatrix(int A[SIZE / 2][SIZE / 2], int B[SIZE / 2][SIZE / 2], int C[SIZE / 2][SIZE / 2]) {
    for (int i = 0; i < SIZE / 2; i++)
        for (int j = 0; j < SIZE / 2; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int A[SIZE / 2][SIZE / 2], int B[SIZE / 2][SIZE / 2], int C[SIZE / 2][SIZE / 2]) {
    for (int i = 0; i < SIZE / 2; i++)
        for (int j = 0; j < SIZE / 2; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void strassenMatrixMultiply(int A[2][2], int B[2][2], int C[2][2]) {
    int P = (A[0][0] + A[1][1]) * (B[0][0] + B[1][1]);
    int Q = (A[1][0] + A[1][1]) * B[0][0];
    int R = A[0][0] * (B[0][1] - B[1][1]);
    int S = A[1][1] * (B[1][0] - B[0][0]);
    int T = (A[0][0] + A[0][1]) * B[1][1];
    int U = (A[1][0] - A[0][0]) * (B[0][0] + B[0][1]);
    int V = (A[0][1] - A[1][1]) * (B[1][0] + B[1][1]);

    C[0][0] = P + S - T + V;
    C[0][1] = R + T;
    C[1][0] = Q + S;
    C[1][1] = P - Q + R + U;
}

void strassen(int A[SIZE][SIZE], int B[SIZE][SIZE], int C[SIZE][SIZE]) {
    int A11[2][2], A12[2][2], A21[2][2], A22[2][2];
    int B11[2][2], B12[2][2], B21[2][2], B22[2][2];
    int C11[2][2], C12[2][2], C21[2][2], C22[2][2];
    int P1[2][2], P2[2][2], P3[2][2], P4[2][2], P5[2][2], P6[2][2], P7[2][2];
    int temp1[2][2], temp2[2][2];

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            A11[i][j] = A[i][j]; A12[i][j] = A[i][j + 2];
            A21[i][j] = A[i + 2][j]; A22[i][j] = A[i + 2][j + 2];
            B11[i][j] = B[i][j]; B12[i][j] = B[i][j + 2];
            B21[i][j] = B[i + 2][j]; B22[i][j] = B[i + 2][j + 2];
        }
    }
    
    addMatrix(A11, A22, temp1);
    addMatrix(B11, B22, temp2);
    strassenMatrixMultiply(temp1, temp2, P1);
    
    addMatrix(A21, A22, temp1);
    strassenMatrixMultiply(temp1, B11, P2);
    
    subMatrix(B12, B22, temp2);
    strassenMatrixMultiply(A11, temp2, P3);
    
    subMatrix(B21, B11, temp2);
    strassenMatrixMultiply(A22, temp2, P4);
    
    addMatrix(A11, A12, temp1);
    strassenMatrixMultiply(temp1, B22, P5);
    
    subMatrix(A21, A11, temp1);
    addMatrix(B11, B12, temp2);
    strassenMatrixMultiply(temp1, temp2, P6);
    
    subMatrix(A12, A22, temp1);
    addMatrix(B21, B22, temp2);
    strassenMatrixMultiply(temp1, temp2, P7);
    
    addMatrix(P1, P4, temp1);
    subMatrix(temp1, P5, temp2);
    addMatrix(temp2, P7, C11);
    
    addMatrix(P3, P5, C12);
    
    addMatrix(P2, P4, C21);
    
    addMatrix(P1, P3, temp1);
    subMatrix(temp1, P2, temp2);
    addMatrix(temp2, P6, C22);
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            C[i][j] = C11[i][j]; C[i][j + 2] = C12[i][j];
            C[i + 2][j] = C21[i][j]; C[i + 2][j + 2] = C22[i][j];
        }
    }
}

void inputMatrix(int matrix[SIZE][SIZE], char name) {
    printf("Enter elements of matrix %c (4x4):\n", name);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c[%d][%d]: ", name, i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void printMatrix(int matrix[SIZE][SIZE]) {
    printf("Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%02d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE];
    int choice;
    clock_t start, end;
    long double cpu_time_used;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input matrices\n");
        printf("2. Multiply matrices using Strassen's algorithm\n");
        printf("3. Print result matrix\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputMatrix(A, 'A');
                inputMatrix(B, 'B');
                break;
            case 2:
                start = clock();
                strassen(A, B, C);
                end = clock();
                cpu_time_used = ((long double) (end - start)) / CLOCKS_PER_SEC;
                printf("Matrix multiplication completed in %Lf seconds.\n", cpu_time_used);
                break;
            case 3:
                printf("Result matrix C:\n");
                printMatrix(C);
                break;
            case 4:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
