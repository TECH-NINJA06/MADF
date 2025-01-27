#include <stdio.h>
#include <string.h>

void Interchange(char **arr, int i, int j) {
    char *temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

int Partition(char **arr, int low, int high) {
    char *pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (1) {
        while (i <= high && strcmp(arr[i], pivot) >= 0) 
            i++;
        while (j >= low && strcmp(arr[j], pivot) < 0)
            j--;

        if (i >= j)
            break;

        Interchange(arr, i, j);
    }

    Interchange(arr, low, j);
    return j;
}

void Select(char **arr, int n, int k) {
    int low = 0, high = n - 1;

    while (low <= high) {
        int j = Partition(arr, low, high);
        for(int i = 0; i < n; i++)
            printf("%s, ", arr[i]);
        printf("j=%d\n",j+1);
        if (j == k) {
            printf("The %dth largest string is: %s\n", k+1, arr[j]);
            return;
        } else if (j > k) {
            high = j - 1;
        } else {
            low = j + 1;
        }
    }
}

int main() {
    char *strings[] = {"mumbai", "pune", "bangalore", "chennai", "goa", "delhi", "agra", "noida", "karnataka", "kanpur", "nashik", "lucknow", "hyderabad"};

    int k;
    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k < 1 || k > 13) {
        printf("Invalid value of k. It should be between 1 and 13.\n");
        return 1;
    }

    Select(strings, 13, k-1);

    return 0;
}