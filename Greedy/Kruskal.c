#include <stdio.h>
#include <time.h>
#define MAX 20
typedef struct {
    int u, v, cost;
} Edge;
Edge heap[MAX], t[MAX];
int parent[MAX], heapSize = 0;
int cost[MAX][MAX];

int Find(int u) {
    while (parent[u] >= 0)
        u = parent[u];
    return u;
}
void Union(int u, int v) { parent[v] = u; }
void InsertHeap(Edge edge) {
    heap[heapSize] = edge;
    int i = heapSize, p;
    while (i > 0) {
        p = (i - 1) / 2;
        if (heap[p].cost <= heap[i].cost)
            break;
        Edge temp = heap[i];
        heap[i] = heap[p];
        heap[p] = temp;
        i = p;
    }
    heapSize++;
}
void Adjust(int index)
{
    int smallest, left, right;
    while (1)
    {
        left = 2 * index + 1;
        right = 2 * index + 2;
        smallest = index;
        if (left < heapSize && heap[left].cost < heap[smallest].cost)
            smallest = left;
        if (right < heapSize && heap[right].cost < heap[smallest].cost)
            smallest = right;
        if (smallest == index)
            break;
        Edge temp = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = temp;
        index = smallest;
    }
}
Edge DeleteMin()
{
    Edge minEdge = heap[0];
    heapSize--;
    heap[0] = heap[heapSize];
    Adjust(0);
    return minEdge;
}
int Kruskal(Edge E[], int cost[][MAX], int n, Edge t[])
{
    int i, j, k, mincost = 0;
    printf("%8s", " ");
    for (i = 0; i < n; i++)
    {
        printf("%5d", i + 1);
    }
    printf("%5s %5s", "j", "k");
    printf("\nparent: ");
    for (i = 0; i < n; i++)
    {
        parent[i] = -1;
        printf("%5d", parent[i]);
    }
    printf("\n");
    i = 0;
    while ((i < n - 1) && (heapSize > 0))
    {
        Edge edge = DeleteMin();
        j = Find(edge.u);
        k = Find(edge.v);
        if (j != k)
        {
            i++;
            t[i - 1] = edge;
            mincost += cost[edge.u][edge.v];
            Union(j, k);
        }
        printf("\nparent: ");
        for (int h = 0; h < n; h++)
        {
            printf("%5d", parent[h]);
        }
        printf("%5d %5d", edge.u, edge.v);
        printf("\n");
        printf("Mincost: %d\n", mincost);
    }
    if (i != n - 1)
    {
        printf("No spanning tree\n");
        return -1;
    }
    else
    {
        return mincost;
    }
}
void printT(int n, Edge t[])
{
    printf("Edge\t j\tnear[j]\n");
    for (int i = 0; i <= n - 2; i++)
    {
        printf("%d\t%2d\t%4d\n", i + 1, t[i].u, t[i].v);
    }
}
int main()
{
    int n, e;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    printf("Enter the number of edges: ");
    scanf("%d", &e);
    Edge E[e];
    printf("Enter the edges (u v cost):\n");
    for (int i = 0; i < e; i++)
    {
        scanf("%d %d %d", &E[i].u, &E[i].v, &E[i].cost);
    }
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            cost[i][j] = 0;
    for (int i = 0; i < e; i++)
    {
        cost[E[i].u][E[i].v] = E[i].cost;
        cost[E[i].v][E[i].u] = E[i].cost;
        InsertHeap(E[i]);
    }
    int minCost = Kruskal(E, cost, n, t);

    if (minCost != -1)
    {
        printf("\nMinimum Cost: %d\n", minCost);
        printT(n, t);
    }
    return 0;
}