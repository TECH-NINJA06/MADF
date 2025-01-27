#include <stdio.h>
#include <string.h>

int binarySearch(char *arr[], int l, int r, char *x) {
    if (r >= l) {
        int mid = l + (r - l) / 2;
        if (strcmp(arr[mid], x) == 0)
            return mid;
        if (strcmp(arr[mid], x) > 0)
            return binarySearch(arr, l, mid - 1, x);
        return binarySearch(arr, mid + 1, r, x);
    }
    return -1;
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    char *arr[n];
    char buffer[100];
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%s", buffer);
        arr[i] = strdup(buffer);
    }

    char x[100];
    printf("Enter element to search: ");
    scanf("%s", x);

    int result = binarySearch(arr, 0, n - 1, x);
    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }

    return 0;
}