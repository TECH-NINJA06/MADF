#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

void display(char a[][MAX], int n){
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("[%d]       ", i + 1);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%s     ", a[i]);
    }
    printf("\n");
}
int binarysearch(char a[][MAX], int low, int high, char *x) {
    if (high >= low)
    {
        int mid = (low + high) / 2;
        display(a, high + 1);
        printf("\nlow: %d\t  mid: %d\t  high: %d\n\n", low + 1,
               mid + 1, high + 1);
        int cmp_result = strcmp(x, a[mid]);
        if (cmp_result == 0)
            return mid;
        else if (cmp_result < 0)
            return binarysearch(a, low, mid - 1, x);
        else
            return binarysearch(a, mid + 1, high, x);
    }
    return -1;
}
int main() {
    int n;
    char x[MAX];
    printf("Enter number of strings: ");
    scanf("%d", &n);
    char a[n][MAX];
    printf("Enter the strings in sorted order:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%s", a[i]);
    }
    printf("Enter the string to search: ");
    scanf("%s", x);
    display(a, n);

    int result = binarysearch(a, 0, n - 1, x);
    if (result != -1)
        printf("\nElement '%s' found at position %d\n", x, result + 1);
    else
        printf("\nElement '%s' not found\n", x);
    printf("\nExecution time: %.6f ms\n", time_ms);
    return 0;
}