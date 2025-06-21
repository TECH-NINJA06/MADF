#include <stdio.h>

#define MAX 10
int y[MAX], x[MAX], p[MAX], w[MAX], m, n, fp, fw, count = 1, soln = 0;
float Bound(int cp, int cw, int k)
{
    float b, c;
    b = cp;
    c = cw;
    for (int i = k + 1; i <= n; i++)
    {
        c = c + w[i];
        if (c < m)
            b = b + p[i];
        else
            return b + (1 - (c - m) / w[i]) * p[i];
    }
    return b;
}
int BKnap(int k, int cp, int cw)
{
    if (cw + w[k] <= m)
    {
        y[k] = 1;
        if (k < n)
            BKnap(k + 1, cp + p[k], cw + w[k]);
        if (k == n && (cp + p[k] > fp))
        {
            fp = cp + p[k];
            fw = cw + w[k];
            for (int j = 1; j <= k; j++)
                x[j] = y[j];
        }
    }
    else
    {
        y[k] = 0;
    }

    if (Bound(cp, cw, k) < fp)
    {
        y[k] = 0;
    }
    else if (Bound(cp, cw, k) >= fp)
    {
        y[k] = 0;
        if (k < n)
            BKnap(k + 1, cp, cw);
        if (k == n && cp > fp)
        {
            fp = cp;
            fw = cw;
            for (int j = 1; j <= k; j++)
            {
                x[j] = y[j];
            }
        }
    }
}

int main()
{
    int i, j;
    fp = 0;
    printf("Enter n:");
    scanf("%d", &n);
    printf("Enter capacity:");
    scanf("%d", &m);
    printf("Enter weights: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    printf("Enter profits: ");
    for (i = 1; i <= n; i++)
        scanf("%d", &p[i]);
    BKnap(1, 0, 0);
    printf("\nBest solution: ");
    for (i = 1; i <= n; i++)
        printf("x%d=%d ", i, x[i]);
    printf("\nMaximum profit: %d\n", fp);
    return 0;
}