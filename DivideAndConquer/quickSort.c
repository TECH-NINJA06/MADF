#include <stdio.h>
#define MAX 100

void quickSort(int arr[], int low, int up);
int partition(int arr[], int low, int up);
void swap(int *a, int *b);
void display(int arr[], int size, int pivotIndex);

int n, k = 1;

int main() {
    int i, arr[MAX];
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%d", &arr[i]);
    }
    printf("\nInitial array: ");
    display(arr, n, -1); 
    quickSort(arr, 0, n - 1);
    printf("\nThe sorted array in descending order is:\n");
    display(arr, n, -1); 
    return 0;
}

void quickSort(int arr[], int low, int up) {
    if (low < up) {
        int pi = partition(arr, low, up);
        printf("\nPass %d: Pivot = %d\n", k++, arr[pi]);
        display(arr, n, pi);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, up);
    }
}

int partition(int arr[], int low, int up) {
    int pivot = arr[low];
    int i = low;
    int j = up;
    while (i < j) {
        while (arr[i] >= pivot && i < up) {
            i++;
        }
        while (arr[j] < pivot) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void display(int arr[], int size, int pivotIndex) {
    printf("[ ");
    for (int i = 0; i < pivotIndex; i++) {
        printf("%d ", arr[i]);
    }
    if (pivotIndex != -1) {
        printf("] %d [ ", arr[pivotIndex]);  
    }
    for (int i = pivotIndex + 1; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("]\n");
}
