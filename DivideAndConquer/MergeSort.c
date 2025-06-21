#include <stdio.h>
#include <string.h>
#define MAX 100
struct record
{
    int id;
    char name[100];
    int age;
};
struct record a[MAX], b[MAX];
void Merge(int low, int mid, int high)
{
    int i = low, j = mid + 1, k = low;
    while (i <= mid && j <= high)
    {
        if (a[i].id <= a[j].id)
        {
            b[k++] = a[i++];
        }
        else
        {
            b[k++] = a[j++];
        }
    }
    while (i <= mid)
    {
        b[k++] = a[i++];
    }
    while (j <= high)
    {
        b[k++] = a[j++];
    }
    for (k = low; k <= high; k++)
    {
        a[k] = b[k];
    }
}
void MergeSort(int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort(low, mid);
        MergeSort(mid + 1, high);
        Merge(low, mid, high);
    }
}
int main()
{
    int i, n;
    printf("\nEnter number of records: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        printf("Enter id, age and name:\n");
        scanf("%d %d", &a[i].id, &a[i].age);
        getchar();
        fgets(a[i].name, sizeof(a[i].name), stdin);
        a[i].name[strcspn(a[i].name, "\n")] = 0;
    }
    MergeSort(0, n - 1);
    printf("\nSorted Records by ID:\n");
    printf("%s\t%15s\t%s\n", "ID", "NAME", "AGE");
    for (i = 0; i < n; i++)
    {
        printf("%d\t%15s\t%d\n", a[i].id, a[i].name, a[i].age);
    }
    return 0;
}
