#include <stdio.h>
int a[] = {73, 83, 23, -56, 43, -11, 85, -18, 73};
int n = 9;
void minMax(int i, int j, int *min, int *max)
{
    int min1, min2, max1, max2;
    if (i == j)
    {
        *min = *max = a[j];
    }
    else if (i == j - 1)
    {
        if (a[i] < a[j])
        {
            *min = a[i];
            *max = a[j];
        }
        else
        {
            *min = a[j];
            *max = a[i];
        }
    }
    else
    {
        int mid = (i + j) / 2;
        minMax(i, mid, &min1, &max1);
        minMax(mid + 1, j, &min2, &max2);
        *min = (min1 < min2) ? min1 : min2;
        *max = (max1 > max2) ? max1 : max2;
        printf("i = %d\tj = %d\tMin = %d\tMax = %d\n", i, j, *min, *max);
    }
}
int main()
{
    int min, max;
    minMax(0, n - 1, &min, &max);
    printf("Minimum element = %d\tMaximum element = %d\n", min, max);
    return 0;
}
