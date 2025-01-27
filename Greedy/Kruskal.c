#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    int parent;
    int rank;
} Subset;

// Function prototypes
int find(Subset subsets[], int i);
void unionSets(Subset subsets[], int x, int y);
int compareEdges(const void *a, const void *b);

void kruskal(int n, int m, Edge edges[]) {
    Subset subsets[n];
    Edge result[n - 1]; 
    int i, e = 0; 
    int mincost = 0;


    qsort(edges, m, sizeof(Edge), compareEdges);


    for (i = 0; i < n; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    i = 0;
    while (e < n - 1 && i < m) {
        Edge nextEdge = edges[i++];
        int x = find(subsets, nextEdge.u);
        int y = find(subsets, nextEdge.v);
        if (x != y) {
            result[e++] = nextEdge;
            mincost += nextEdge.weight;
            unionSets(subsets, x, y);
        }
    }

    if (e != n - 1) {
        printf("No Spanning Tree\n");
        return;
    }

    printf("Edges in the Minimum Spanning Tree:\n");
    for (i = 0; i < e; i++) {
        printf("(%d, %d) -> %d\n", result[i].u + 1, result[i].v + 1, result[i].weight);
    }
    printf("Total cost of the Minimum Spanning Tree: %d\n", mincost);
}

int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);  // Path compression
    }
    return subsets[i].parent;
}

void unionSets(Subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);
    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compareEdges(const void *a, const void *b) {
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

int main() {
    int n, m;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the number of edges: ");
    scanf("%d", &m);

    Edge edges[m];
    printf("Enter the edges (u v weight) one by one (1-based indexing):\n");
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
        edges[i].u--; 
        edges[i].v--;
    }

    kruskal(n, m, edges);

    return 0;
}
