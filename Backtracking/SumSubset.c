#include <stdio.h>
#include <stdlib.h>

int n, m;
int w[100], x[100];

void printTree(int spaces, int s, int k, int r) {
    for (int i = 0; i < spaces; i++)
        printf(" ");  // Indentation for tree structure
    printf("[ %d | %d | %d ]\n", s, k, r);  // Print node
}

void SumOfSub(int s, int k, int r, int spaces) {
    printTree(spaces, s, k, r);  // Print current node

    if (k >= n)  // Base case: Stop if index exceeds
        return;

    x[k] = 1;
    if (s + w[k] <= m) {  // Left branch (Include w[k])
        for (int i = 0; i < spaces; i++) printf(" ");
        printf("/\n");
        SumOfSub(s + w[k], k + 1, r - w[k], spaces + 4);
    }

    x[k] = 0;
    if (s + r - w[k] >= m) {  // Right branch (Exclude w[k])
        for (int i = 0; i < spaces; i++) printf(" ");
        printf("\\\n");
        SumOfSub(s, k + 1, r - w[k], spaces + 4);
    }
}

int main() {
    int r = 0;
    printf("Enter size of set: ");
    scanf("%d", &n);
    printf("Enter elements of set: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
        r += w[i];
    }
    printf("Enter sum: ");
    scanf("%d", &m);

    printf("\n Tree Structure:\n");
    SumOfSub(0, 0, r, 0);  // Start from root

    return 0;
}
