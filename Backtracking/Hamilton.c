#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define TRUE 1
#define FALSE 0
int G[MAX][MAX];
void Hamiltonian(int x[], int n, int k);
solnCount = 0, startVertex = 0;

int main() {
    int n, x[MAX], k;
    printf("\nEnter the number of nodes:");
    scanf("%d", &n);
    printf("Enter the Adjacency Matrix:\n");
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            scanf("%d", &G[i][j]);
    }
    startVertex = 1;
    x[1] = startVertex;
    for (int i = 2; i <= n; i++)
        x[i] = 0;
    Hamiltonian(x, n, 2);
    printf("\nTotal number of solutions: %d\n", solnCount);
    return 0;
}

void nextval(int x[], int n, int k) {
    do {
        x[k] = (x[k] + 1) % (n + 1);
        if (x[k] == 0)
            return;
        if (G[x[k - 1]][x[k]] != 0) {
            for (int j = 1; j < k; j++) {
                if (x[j] == x[k]) {
                    break;
                }
            }
            if (j == k) {
                if ((k < n) || (k == n && G[x[n]][x[1]] != 0))
                    return;
            }
        }
    } while (TRUE);
}
void Hamiltonian(int x[], int n, int k) {
    do
    {
        nextval(x, n, k);
        if (x[k] == 0) {
            return;
        }
        if (k == n) {
            printf("Solution: ");
            for (int j = 1; j <= n; j++) {
                printf("%d ", x[j]);
            }
            printf("%d\n", x[1]);
            if (startVertex == 1)
                ++solnCount;
        }
        else {
            Hamiltonian(x, n, k + 1);
        }
    } while (TRUE);
}