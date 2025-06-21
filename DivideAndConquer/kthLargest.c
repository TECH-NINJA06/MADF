#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define BOLD "\033[1m"
#define RESET "\033[0m"
int n = 13;

void display(char a[], int p, int q, int pivotIndex) {
    printf("\n\n");
    for (int i = 0; i < p; i++)
        printf("%c ", a[i]);
    printf("[ ");
    for (int i = p; i <= q; i++) {
        if (i == pivotIndex) {
            printf(BOLD "%c" RESET " ", a[i]);
        } else {
            printf("%c ", a[i]);
        }
    }
    printf("] ");
    for (int i = q + 1; i < n; i++)
        printf("%c ", a[i]);
}


void interchange(char a[], int i, int j) {
    char temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
int partition(char a[], int p, int q) {
    char pivot = a[p];
    int i = p + 1;
    int j = q;
    display(a, p, q, p);
    while (true) {
        while (i <= q && a[i] < pivot)
            i++;
        while (j >= p && a[j] > pivot)
            j--;
        if (i < j) {
            interchange(a, i, j);
            display(a, p, q, p);
        } else {
            break;
        }
    }
    interchange(a, p, j);
    display(a, p, q, j);
    printf("\tj = %d", j + 1);
    return j;
}
void select(char a[], int k) {
    int low = 0, up = n - 1;
    int j;
    do {
        j = partition(a, low, up);
        if (k < j) {
            up = j - 1;
        } else if (k > j) {
            low = j + 1;
        } else {
            printf("\nThe %dth smallest element is: %c\n", k + 1, a[k]);
            return;
        }
    } while (true);
}

int main() {
    int k = 4;
    char a[13] = {'W', 'Y', 'S', 'A', 'G', 'I', 'O', 'V', 'C', 'H', 'P', 'B', 'R'};

    select(a, k - 1);

    return 0;
}