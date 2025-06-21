#include <stdio.h>
#define TRUE 1
#define FALSE 0
#define MAX 20

int n, solutionCount = 0;
int G[MAX][MAX], x[MAX];

void nextValue(int k, int m);
void graphColoring(int k, int m);

int main() {
    int i, j, max = 0, m;

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);
    for (i = 1; i <= n; i++)
        x[i] = 0;
    printf("Enter the adjacency matrix:\n");
    m = 0;
    for (i = 1; i <= n; i++) {
        max = 0;
        for (j = 1; j <= n; j++) {
            scanf("%d", &G[i][j]);
            if (G[i][j] == 1)
                max++;
        }
        if (max > m)
            m = max;
    }
   
    for (i = 1; i <= m; i++) {
        solutionCount = 0;
        graphColoring(1, i);
        if (solutionCount > 0) {
            printf("Chromatic number: %d\n", i);
            printf("Total solutions for chromatic number %d: %d\n", i, solutionCount);
            break;
        }
        for (j = 1; j <= n; j++)
            x[j] = 0;
    }
    return 0;
}

void nextValue(int k, int m) {
    int j;
    do {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) {
            return;
        }
        for (j = 1; j <= n; j++) {
            if (G[k][j] == 1 && x[k] == x[j]) {
                break;
            }
        }
        if (j == n + 1) {
            break;
        }
    } while (TRUE);
}


void graphColoring(int k, int m) {
    int checked = 0;
    do {
        nextValue(k, m);
        if (x[k] == 0)
            return;
        if (k == n) {
            if (!checked) {
                ++solutionCount;
                checked = 1;
                printf("Solution vector: ");
                for (int i = 1; i <= n; i++)
                    printf("%d ", x[i]);
                printf("\n");
            }
        }
        else
            graphColoring(k + 1, m);
    } while (TRUE);
}

