#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void printMatrix(int V, int matrix[V][V]) {
    printf("\nCost Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF)
                printf("INF\t");
            else
                printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

void printDistanceTable(int V, int dist[V], int iteration) {
    printf("\nDistance Matrix after iteration %d:\n", iteration);
    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("INF\t");
        else
            printf("%d\t", dist[i]);
    }
    printf("\n");
}

void printShortestPaths(int V, int src, int dist[V], int parent[V]) {
    printf("\nShortest Paths Table:\n");
    printf("Src\tDest\tLength\tPath\n");
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("%d\t%d\t", src, i);
            if (dist[i] == INF) {
                printf("INF\t-\n");
            } else {
                printf("%d\t", dist[i]);
                
                int path[V], count = 0;
                for (int v = i; v != -1; v = parent[v])
                    path[count++] = v;

                for (int j = count - 1; j >= 0; j--)
                    printf("%d ", path[j]);
                
                printf("\n");
            }
        }
    }
}

void BellmanFord(int V, int graph[V][V], int src) {
    int dist[V], parent[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[src] = 0;

    printMatrix(V, graph);

    for (int k = 1; k < V; k++) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
        printDistanceTable(V, dist, k);
    }

    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                printf("\nGraph contains a negative weight cycle!\n");
                return;
            }
        }
    }

    printShortestPaths(V, src, dist, parent);
}

int main() {
    int V = 5;
    int graph[5][5] = {
        {0, 6, INF, 7, INF},
        {INF, 0, 5, 8, -4},
        {INF, -2, 0, INF, INF},
        {INF, INF, -3, 0, 9},
        {2, INF, 7, INF, 0}
    };

    int src = 0;
    BellmanFord(V, graph, src);

    return 0;
}
