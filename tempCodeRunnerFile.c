#include <stdio.h>
#include <limits.h>
#include <string.h>

#define N 20
#define INF INT_MAX

struct key
{
    int w, r, c;
};

void getUnsuccessfulSearchProbs(int q[N], int n)
{
    for (int i = 0; i <= n; i++)
    {
        scanf("%d", &q[i]);
    }
}

void getSuccessfulSearchProbs(int p[N], int n)
{
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }
}

int findRoot(struct key g[][N], int i, int j)
{
    int minCost = INF, root;
    for (int m = g[i][j - 1].r; m <= g[i + 1][j].r; m++)
    {
        int currentCost = g[i][m - 1].c + g[m][j].c;
        if (currentCost < minCost)
        {
            minCost = currentCost;
            root = m;
        }
    }
    return root;
}

// Recursive function to print the tree in a readable format
void printTree(int r[][N], int i, int j, char *a[], int level)
{
    if (i >= j) return;

    int root = r[i][j];
    if (root == 0) return;

    // Print the root at the current level
    for (int l = 0; l < level; l++) {
        printf("  ");
    }
    printf("%s\n", a[root - 1]);

    // Recursively print left and right subtrees
    printTree(r, i, root - 1, a, level + 1);
    printTree(r, root, j, a, level + 1);
}

void optimalBST(struct key g[][N], int q[N], int p[N], int n, char *a[N])
{
    int k;
    printf("\n\n");

    // Initialize base cases
    for (int i = 0; i <= n; i++)
    {
        g[i][i].w = q[i];
        g[i][i].r = g[i][i].c = 0;
        g[i][i + 1].w = q[i] + q[i + 1] + p[i + 1];
        g[i][i + 1].r = i + 1;
        g[i][i + 1].c = q[i] + q[i + 1] + p[i + 1];
    }

    // Print the initial matrices for w, c, and r for base cases
    printf("w (initial):\n");
    for (int i = 0; i <= n; i++) {
        printf("%d\t", g[i][i].w);
    }
    printf("\n\n");

    printf("c (initial):\n");
    for (int i = 0; i <= n; i++) {
        printf("%d\t", g[i][i].c);
    }
    printf("\n\n");

    printf("r (initial):\n");
    for (int i = 0; i <= n; i++) {
        printf("%d\t", g[i][i].r);
    }
    printf("\n\n");

    // Print values for gap 1
    printf("w for gap 1:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", g[i][i + 1].w);
    }
    printf("\n");

    printf("c for gap 1:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", g[i][i + 1].c);
    }
    printf("\n");

    printf("r for gap 1:\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t", g[i][i + 1].r);
    }
    printf("\n\n");

    // Main DP to compute w, c, r values for larger gaps
    for (int m = 2; m <= n; m++)
    {
        for (int i = 0; i <= n - m; i++)
        {
            int j = i + m;
            g[i][j].w = g[i][j - 1].w + p[j] + q[j];
            k = findRoot(g, i, j);
            g[i][j].c = g[i][j].w + g[i][k - 1].c + g[k][j].c;
            g[i][j].r = k;
        }
    }

    // Print the final w, c, r tables after DP computation
    printf("Final w, c, r matrices after DP computation:\n");
    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            printf("w[%d][%d] = %d\t", i, j, g[i][j].w);
        }
        printf("\n");
    }

    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            printf("c[%d][%d] = %d\t", i, j, g[i][j].c);
        }
        printf("\n");
    }

    for (int i = 0; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            printf("r[%d][%d] = %d\t", i, j, g[i][j].r);
        }
        printf("\n");
    }

    printf("\nMinimum cost of the OBST is: %d\n", g[0][n].c);
    printf("Root of the optimal BST: %s\n", a[g[0][n].r - 1]);

    // Print the OBST in tree format
    printf("\nOptimal Binary Search Tree:\n");
    printTree(g[0], 0, n, a, 0);
}

int main()
{
    int n;
    char *a[N] = {"case", "double", "return", "switch", "union"};
    int p[N], q[N];
    struct key g[N][N];

    printf("Enter the number of identifiers: ");
    scanf("%d", &n);

    printf("Enter the probabilities for a successful search: ");
    getSuccessfulSearchProbs(p, n);

    printf("Enter the probabilities for an unsuccessful search: ");
    getUnsuccessfulSearchProbs(q, n);

    optimalBST(g, q, p, n, a);

    return 0;
}
