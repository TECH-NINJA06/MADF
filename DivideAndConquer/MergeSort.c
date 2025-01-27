#include <stdio.h>
#include <stdlib.h>


void merge(int arr[], int temp[], int left, int mid, int right);
void merge_sort(int arr[], int temp[], int left, int right);

void merge_sort(int arr[], int temp[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        printf("Dividing: ");
        for (int i = 0; i <= left - 1; i++) printf("%d ", arr[i]);
        printf("[ ");
        for (int i = left; i <= mid; i++) printf("%d ", arr[i]);
        printf("| ");
        for (int i = mid + 1; i <= right; i++) printf("%d ", arr[i]);
        printf("] ");
        for (int i = right + 1; i < MAX && arr[i] != 0; i++) printf("%d ", arr[i]);
        printf("\n");

        merge_sort(arr, temp, left, mid);
        merge_sort(arr, temp, mid + 1, right);

        merge(arr, temp, left, mid, right);

        // Print merging step
        printf("Merging: ");
        for (int i = 0; i <= left - 1; i++) printf("%d ", arr[i]);
        printf("[ ");
        for (int i = left; i <= right; i++) printf("%d ", arr[i]);
        printf("] ");
        for (int i = right + 1; i < MAX && arr[i] != 0; i++) printf("%d ", arr[i]);
        printf("\n");
    }
}

void merge(int arr[], int temp[], int left, int mid, int right) {
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }
    while (j <= right) {
        temp[k++] = arr[j++];
    }

    for (i = left; i <= right; i++) {
        arr[i] = temp[i];
    }
}
#define MAX 100

int main() {
    int arr[MAX], temp[MAX];
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    merge_sort(arr, temp, 0, n - 1);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}