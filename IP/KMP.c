#include <stdio.h>
#include <string.h>

void computeFailureFunction(char *pattern, int *f) {
    int m = strlen(pattern);
    int i = 1, j = 0;
    f[0] = 0;

    while (i < m) {
        if (pattern[i] == pattern[j]) {
            f[i] = j + 1;
            i++;
            j++;
        }
        else if (j > 0) {
            j = f[j - 1];
        }
        else {
            f[i] = 0;
            i++;
        }
    }
}

int KMPMatch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int f[256];
    computeFailureFunction(pattern, f);

    int i = 0, j = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            if (j == m - 1) {
                return i - m + 1; 
            }
            i++;
            j++;
        }
        else if (j > 0) {
            j = f[j - 1]; 
        }
        else {
            i++;
        }
    }
    return -1;
}

int main() {
    char text[256], pattern[256];

    scanf("%s", text);
    scanf("%s", pattern);

    int index = KMPMatch(text, pattern);
    printf("%d\n", index);

    return 0;
}
