#include <stdio.h>
#define BOLD "\033[1m"
#define RESET "\033[0m"
int a[] = {43, -12, 11, 58, -5, 29, 65, -17, 37};
int n = 9;
void display(int p, int q, int pivotIndex, int placed)
{
    printf("\n\n");
    for (int i = 0; i < p; i++)
        printf("%d ", a[i]);
    printf("[ ");
    for (int i = p; i <= q; i++)
    {
        if (i == pivotIndex)
        {
            if (placed)
            {
                printf("] " BOLD "%d" RESET " [ ", a[i]);
            }
            else
                printf(BOLD "%d" RESET " ", a[i]);
        }
        else
        {
            printf("%d ", a[i]);
        }
    }

    printf("] ");
    for (int i = q + 1; i < n; i++)
        printf("%d ", a[i]);
}
void interchange(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}
int partition(int a[], int p, int q)
{
    int pivot = a[p];
    int i = p + 1;
    int j = q;
    while (1)
    {
        while (i <= q && a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i < j)
        {
            interchange(a, i, j);
            display(p, q, j, 1);
            display(p, q, p, 0);
        }
        else
        {
            break;
        }
    }
    interchange(a, p, j);
    display(p, q, j, 1);
    printf("\tj = %d", j + 1);
    return j;
}
void quickSort(int p, int q)
{
    if (p < q)
    {
        int pivotIndex = partition(a, p, q);
        quickSort(p, pivotIndex - 1);
        quickSort(pivotIndex + 1, q);
    }
}
int main()
{
    display(0, n - 1, 0, 0);
    quickSort(0, n - 1);
    printf("\n\nThe sorted array is:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);
    printf("\n");
    return 0;
}
