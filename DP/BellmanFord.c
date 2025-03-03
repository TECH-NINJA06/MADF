#include <stdio.h>
#include <limits.h>

#define INF INT_MAX

void BellmanFord(int V, int E, int graph[][3], int src) {
    int dist[V];

    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int k = 1; k < V; k++) {
        for (int i = 0; i < E; i++) {
            int u = graph[i][0];
            int v = graph[i][1];
            int weight = graph[i][2];

            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = graph[i][0];
        int v = graph[i][1];
        int weight = graph[i][2];

        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            printf("Graph contains negative weight cycle!\n");
            return;
        }
    }

    printf("Vertex Distance from Source:\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

int main() {
    int V = 5;
    int E = 8;

    int graph[][3] = {
        {0, 1, -1}, {0, 2, 4},
        {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5},
        {3, 1, 1}, {4, 3, -3}
    };

    int src = 0;
    BellmanFord(V, E, graph, src);

    return 0;
}
