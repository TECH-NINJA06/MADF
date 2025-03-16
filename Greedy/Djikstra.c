#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_N 100 

int minDistance(int dist[], bool s[], int n) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < n; v++) {
        if (!s[v] && dist[v] < min) {
            min = dist[v];
            min_index = v;
        }
    }

    return min_index;
}

void printPath(int parent[], int j) {
    if (parent[j] == -1) {
        printf("%d", j + 1); 
        return;
    }
    printPath(parent, parent[j]);
    printf(" -> %d", j + 1);
}

void shortestPath(int v, int cost[MAX_N][MAX_N], int dist[], int n) {
    bool s[MAX_N] = {false}; 
    int parent[MAX_N]; 

    for (int i = 0; i < n; i++) {
        s[i] = false;
        dist[i] = cost[v][i]; 
        parent[i] = (cost[v][i] == INT_MAX) ? -1 : v; 
    }

    s[v] = true;
    dist[v] = 0; 
    parent[v] = -1; 

    printf("s[1:%d] = false\n\n", n);

    for (int i = 1; i < n; i++) {
        int u = minDistance(dist, s, n);
        s[u] = true;

        printf("Iteration %d:    u = %d\n", i, u + 1);
        printf("s[%d] = true\n", u + 1);
        printf("s[");

        bool first = true;
        for (int j = 0; j < n; j++) {
            if (!s[j]) {
                if (!first) printf(", ");
                printf("%d", j + 1);
                first = false;
            }
        }
        printf("] = false\n");

        for (int w = 0; w < n; w++) {
            if (!s[w] && cost[u][w] != INT_MAX && dist[u] + cost[u][w] < dist[w]) {
                dist[w] = dist[u] + cost[u][w];
                parent[w] = u;
            }
        }

        printf("d[1] = %d", dist[0]);
        for (int j = 1; j < n; j++) {
            if (dist[j] == INT_MAX) {
                printf(", d[%d] = INF", j + 1);
            } else printf(", d[%d] = %d", j + 1, dist[j]);
        }
        printf("\n\n");
    }

    printf("\n%-12s %-8s %s\n", "Src to Dest", "Cost", "Path");
    printf("--------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (i != v) {
            printf("(%d -> %d)      %-8d ", v + 1, i + 1, dist[i]);
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int n = 8; 
    int cost[MAX_N][MAX_N] = {
        {0, 40, 20, 10, 50, INT_MAX, 60, INT_MAX},
        {INT_MAX, 0, 1, INT_MAX, 5, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, INT_MAX, 0, INT_MAX, 2, 10, 2, INT_MAX},
        {INT_MAX, INT_MAX, 5, 0, INT_MAX, INT_MAX, 5, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 3, INT_MAX, 5},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 3, 5},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0, 3},
        {INT_MAX, 2, 3, 5, INT_MAX, INT_MAX, INT_MAX, 0}
    };
    
    int dist[MAX_N];
    int source = 0;

    shortestPath(source, cost, dist, n);

    return 0;
}
