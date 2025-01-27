#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void prim(int n, int cost[n][n]) {
    int t[n - 1][2]; 
    int mincost = 0;
    int near[n]; 

    int k, l, min = INF;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    t[0][0] = k;
    t[0][1] = l;
    mincost += cost[k][l];

    for (int i = 0; i < n; i++) {
        if (cost[i][k] < cost[i][l]) {
            near[i] = k;
        } else {
            near[i] = l;
        }
    }
    near[k] = near[l] = -1;

    for (int i = 1; i < n - 1; i++) {
        int min = INF, j;
        for (int m = 0; m < n; m++) {
            if (near[m] != -1 && cost[m][near[m]] < min) {
                min = cost[m][near[m]];
                j = m;
            }
        }

        t[i][0] = j;
        t[i][1] = near[j];
        mincost += cost[j][near[j]];
        near[j] = -1;

        for (int k = 0; k < n; k++) {
            if (near[k] != -1 && cost[k][near[k]] > cost[k][j]) {
                near[k] = j;
            }
        }

        printf("Iteration %d:\n", i);
        printf("Near array: ");
        for (int m = 0; m < n; m++) {
            printf("%d ", near[m]);
        }
        printf("\n");
        printf("Cost for each node: ");
        for (int m = 0; m < n; m++) {
            if (near[m] != -1) {
                printf("%d ", cost[m][near[m]]);
            } else {
                printf("INF ");
            }
        }
        printf("\n");
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("(%d, %d)\n", t[i][0] + 1, t[i][1] + 1); // +1 to convert to 1-based indexing
    }
    printf("Total cost of the Minimum Spanning Tree: %d\n", mincost);
}

int main() {
    int n;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    int cost[n][n];
    printf("Enter the adjacency matrix (use %d for infinity):\n", INF);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &cost[i][j]);
        }
    }

    prim(n, cost);

    return 0;
}
