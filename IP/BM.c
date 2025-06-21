#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

void lastOccurrenceFunction(char *pattern, int *last) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        last[i] = -1;
    for (int i = 0; i < strlen(pattern); i++)
        last[(unsigned char)pattern[i]] = i;
}

int boyerMooreMatch(char *text, char *pattern) {
    int n = strlen(text);
    int m = strlen(pattern);
    int last[ALPHABET_SIZE];
    lastOccurrenceFunction(pattern, last);

    int i = m - 1;
    int j = m - 1;

    while (i <= n - 1) {
        if (text[i] == pattern[j]) {
            if (j == 0)
                return i;
            else {
                i--;
                j--;
            }
        } else {
            int l = last[(unsigned char)text[i]];
            i = i + m - (j < l + 1 ? j : l + 1); 
            j = m - 1;
        }
    }

    return -1;
}

int main() {
    char text[256], pattern[256];

    scanf("%s", text);
    scanf("%s", pattern);

    int index = boyerMooreMatch(text, pattern);
    printf("%d\n", index);

    return 0;
}
