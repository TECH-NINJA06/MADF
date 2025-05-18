#include <stdio.h>
#include <string.h>

#define MAX 100

typedef struct {
    int length;
    char arrow;
} LCSResult;

void lcs(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);
    LCSResult L[MAX][MAX];
    int visited[MAX][MAX] = {0};

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                L[i][j].length = 0;
                L[i][j].arrow = ' ';
            } else if (X[i - 1] == Y[j - 1]) {
                L[i][j].length = 1 + L[i - 1][j - 1].length;
                L[i][j].arrow = '\\'; 
            } else if (L[i - 1][j].length >= L[i][j - 1].length) {
                L[i][j].length = L[i - 1][j].length;
                L[i][j].arrow = '^'; 
            } else {
                L[i][j].length = L[i][j - 1].length;
                L[i][j].arrow = '<';
            }
        }
    }

    int index = L[m][n].length;
    char lcs_seq[index + 1];
    lcs_seq[index] = '\0';

    int i = m, j = n;
    while (i > 0 && j > 0) {
        visited[i][j] = 1; 
        if (L[i][j].arrow == '\\') {
            lcs_seq[--index] = X[i - 1];
            i--;
            j--;
        } else if (L[i][j].arrow == '^') {
            i--;
        } else {
            j--;
        }
    }

    printf("\n\n    ");
    for (int j = 0; j <= n; j++) {
        if (j == 0)
            printf("       ");
        else
            printf("  %c  ", Y[j - 1]);
    }
    printf("\n");

    for (int i = 0; i <= m; i++) {
        if (i == 0)
            printf("     ");
        else
            printf(" %c   ", X[i - 1]);

        for (int j = 0; j <= n; j++) {
            char display_arrow = visited[i][j] ? L[i][j].arrow : ' ';
            printf(" %c%2d ", display_arrow, L[i][j].length);
        }
        printf("\n");
    }

    
    printf("\nLCS Length: %d\n", L[m][n].length);
    printf("\nLCS: %s\n", lcs_seq);
}


int main() {
    char X[MAX], Y[MAX];

    printf("Enter first string: ");
    scanf("%s", X);

    printf("Enter second string: ");
    scanf("%s", Y);

    lcs(X, Y);

    return 0;
}