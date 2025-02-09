#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_LEN 100

void merge(char arr[][MAX_LEN], char temp[][MAX_LEN], int left, int mid, int right);
void merge_sort(char arr[][MAX_LEN], char temp[][MAX_LEN], int left, int right);

void merge_sort(char arr[][MAX_LEN], char temp[][MAX_LEN], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        merge_sort(arr, temp, left, mid);
        merge_sort(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);
    }
}

void merge(char arr[][MAX_LEN], char temp[][MAX_LEN], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (strcmp(arr[i], arr[j]) <= 0) {
            strcpy(temp[k++], arr[i++]);
        } else {
            strcpy(temp[k++], arr[j++]);
        }
    }

    while (i <= mid) {
        strcpy(temp[k++], arr[i++]);
    }
    while (j <= right) {
        strcpy(temp[k++], arr[j++]);
    }

    for (i = left; i <= right; i++) {
        strcpy(arr[i], temp[i]);
    }
}

int main() {
    char arr[MAX][MAX_LEN], temp[MAX][MAX_LEN];
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    printf("Enter strings: ");
    for (int i = 0; i < n; i++) {
        scanf("%s", arr[i]);
    }

    merge_sort(arr, temp, 0, n - 1);

    printf("Sorted strings: ");
    for (int i = 0; i < n; i++) {
        printf("%s ", arr[i]);
    }
    printf("\n");

    return 0;
}
