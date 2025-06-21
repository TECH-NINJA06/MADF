#include <stdio.h>
#include <string.h>

#define MAX 100

void lcs(char *X, char *Y) {
    int n = strlen(X);
    int m = strlen(Y);
    int L[MAX + 1][MAX + 1];
    
    for (int i = 0; i <= n; i++)
        L[i][0] = 0;
    for (int j = 0; j <= m; j++)
        L[0][j] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
        }
    }

    int index = L[n][m];
    char lcs_seq[index + 1];
    lcs_seq[index] = '\0';

    int i = n, j = m;
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs_seq[--index] = X[i - 1];
            i--;
            j--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    printf("%d\n", L[n][m]);  
    printf("%s\n", lcs_seq);  
}

int main() {
    char X[MAX], Y[MAX];
    scanf("%s", X);
    scanf("%s", Y);
    lcs(X, Y);
    return 0;
}
