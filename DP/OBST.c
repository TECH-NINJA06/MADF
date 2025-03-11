#include <stdio.h>
#include <limits.h>

#define N 5

void optimalBST(int keys[], int freq[], int n) {
    int cost[n+1][n+1];
    for(int i = 0; i <= n; i++) {
        cost[i][i] = 0;
    }
    int root[n+1][n+1];
    for(int i = 0; i <= n; i++) {
        root[i][i] = 0;
    }

    int sum[n+1][n+1];
    for(int i = 0; i <= n; i++) {
        sum[i][i] = 0;
    }

    for (int i = 0; i < n; i++) {
        sum[i][i] = freq[i];
        for (int j = i + 1; j < n; j++) {
            sum[i][j] = sum[i][j - 1] + freq[j];
        }
    }

    for (int length = 1; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;
            cost[i][j] = INT_MAX;
            
            for (int r = i; r <= j; r++) {
                int c = ((r > i) ? cost[i][r - 1] : 0) +
                        ((r < j) ? cost[r + 1][j] : 0) +
                        sum[i][j];
                
                if (c < cost[i][j]) {
                    cost[i][j] = c;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("Cost Table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i)
                printf("%4d ", cost[i][j]);
            else
                printf("     ");
        }
        printf("\n");
    }

    printf("\nRoot Table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j >= i)
                printf("%4d ", root[i][j]);
            else
                printf("     ");
        }
        printf("\n");
    }
}

int main() {
    int keys[N] = {10, 20, 30, 40, 50};
    int freq[N] = {3, 5, 8, 4, 10};

    optimalBST(keys, freq, N);
    return 0;
}
