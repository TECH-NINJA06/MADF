#include <stdio.h>
#include <time.h>
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
    printf("\ndist[%d]  ", iteration);

    for (int i = 0; i < V; i++) {
        if (dist[i] == INF)
            printf("INF   ");
        else
            printf("%-5d ", dist[i]);
    }
}


void printShortestPaths(int V, int src, int dist[V], int parent[V]) {
    printf("\n\nShortest Paths Table:\n");
    printf("Src\tDest\tLength\tPath\n");
    for (int i = 0; i < V; i++) {
        if (i != src) {
            printf("%d\t%d\t", src+1, i+1);
            if (dist[i] == INF) {
                printf("INF\t-\n");
            } else {
                printf("%d\t", dist[i]);
                
                int path[V], count = 0;
                for (int v = i; v != -1; v = parent[v])
                    path[count++] = v;

                for (int j = count - 1; j >= 0; j--)
                    printf("%d ", path[j]+1);
                
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

    printf("\nDistance Table:");
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
    clock_t start, end;
    double time_taken;
    int V = 7;
    int cost[7][7] = {
        {0, 4, INF, 7, -3, INF, 4},
        {6, 0, -2, 6, INF, 1, INF},
        {4, 3, 0, INF, 1, 4, INF},
        {3, INF, 3, 0, INF, 5, 5},
        {INF, 4, INF, 2, 0, INF, INF},
        {-1, 2, -2, INF, -2, 1, 1},
        {INF, INF, INF, 6, -2, 1, 0}
    };

    int src = 0;
    start = clock();
    BellmanFord(V, cost, src);
    end = clock();
    time_taken = (((double)(end - start)) / CLOCKS_PER_SEC) * 1000;

    printf("\nExecution Time: %.6f ms\n", time_taken);

    return 0;
}
