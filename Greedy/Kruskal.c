#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

struct Edge
{
    int u, v, weight;
};

struct Subset
{
    int parent;
    int rank;
};

int find(struct Subset subsets[], int i);
void unionSets(struct Subset subsets[], int x, int y);
void heapSort(struct Edge arr[], int n);
void heapify(struct Edge arr[], int n, int i);
void printParents(struct Subset subsets[], int n);

void kruskal(int n, int m, struct Edge edges[])
{
    struct Subset subsets[n];
    struct Edge result[n - 1];
    int i, e = 0;
    int mincost = 0;

    heapSort(edges, m);

    for (i = 0; i < n; i++)
    {
        subsets[i].parent = -2;
        subsets[i].rank = 0;
    }
    printParents(subsets, n);
    i = 0;
    while (e < n - 1 && i < m)
    {
        struct Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.u);
        int y = find(subsets, nextEdge.v);

        if (x != y)
        {
            result[e++] = nextEdge;
            mincost += nextEdge.weight;
            unionSets(subsets, x, y);
        }

        printf("After considering edge (%d, %d):\n", nextEdge.u + 1, nextEdge.v + 1);
        printParents(subsets, n);
    }

    if (e != n - 1)
    {
        printf("No Spanning Tree\n");
        return;
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; i++)
    {
        printf("(%d, %d) -> %d\n", result[i].u + 1, result[i].v + 1, result[i].weight);
    }
    printf("Total cost of the Minimum Spanning Tree: %d\n", mincost);
}

int find(struct Subset subsets[], int i)
{
    while (subsets[i].parent >= 0)
    {
        i = subsets[i].parent;
    }
    return i;
}

void unionSets(struct Subset subsets[], int x, int y)
{
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (rootX != rootY)
    {
        if (subsets[rootY].rank < subsets[rootX].rank)
        {
            subsets[rootY].parent = rootX;
        }
        else if (subsets[rootY].rank > subsets[rootX].rank)
        {
            subsets[rootX].parent = rootY;
        }
        else
        {
            subsets[rootX].parent = rootY;
            subsets[rootY].rank--;
        }
    }
}

void heapSort(struct Edge arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        struct Edge temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        heapify(arr, i, 0);
    }
}

void heapify(struct Edge arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left].weight > arr[largest].weight)
    {
        largest = left;
    }
    if (right < n && arr[right].weight > arr[largest].weight)
    {
        largest = right;
    }
    if (largest != i)
    {
        struct Edge temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest);
    }
}

void printParents(struct Subset subsets[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Vertex %d: Parent = %d\n", i + 1, subsets[i].parent + 1);
    }
    printf("\n");
}

int main()
{
    int n = 8, m = 14;
    struct Edge edges[] = {
        {1, 4, 1}, {4, 5, 1}, {0, 2, 2}, {1, 3, 2}, {3, 5, 2}, {4, 7, 2}, {6, 7, 1}, {1, 2, 3}, {2, 7, 3}, {3, 4, 3}, {4, 6, 3}, {2, 4, 4}, {5, 6, 4}, {0, 1, 5}
    };

    kruskal(n, m, edges);
    return 0;
}
