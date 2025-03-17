#include <stdio.h>
#include <limits.h>
#define INF INT_MAX

struct Edge {
    int source;
    int dest;
    int cost;
};

void printVicinity(int n, int selected[], int costs[]) {
   for (int i = 0; i < n; i++) {
        if (selected[i]) {
            printf("Node %d: 0\n", i + 1);
        } else if (costs[i] != INF) {
            printf("Node %d: %d\n", i + 1, costs[i]); 
        } else {
            printf("Node %d: INF\n", i + 1);
        }
    }
    printf("\n");
}

void Prim(struct Edge Edges[], int numEdges, int n) {
    int mincost = 0;   
    int selected[n];  
    int edge = 0;
    int costs[n]; 

    for (int i = 0; i < n; i++) {
        selected[i] = 0; 
        costs[i] = INF;
    }

    selected[0] = 1;  
    costs[0] = 0; 

    while (edge < n - 1) {
        int min = INF;
        int x = -1, y = -1;

        for (int i = 0; i < numEdges; i++) {
            if (selected[Edges[i].source - 1] && !selected[Edges[i].dest - 1]) {
                if (Edges[i].cost < costs[Edges[i].dest - 1]) {
                    costs[Edges[i].dest - 1] = Edges[i].cost;
                }
                if (Edges[i].cost < min) {
                    min = Edges[i].cost;
                    x = Edges[i].source;
                    y = Edges[i].dest;
                }
            } else if (selected[Edges[i].dest - 1] && !selected[Edges[i].source - 1]) {
                if (Edges[i].cost < costs[Edges[i].source - 1]) {
                    costs[Edges[i].source - 1] = Edges[i].cost;
                }
                if (Edges[i].cost < min) {
                    min = Edges[i].cost;
                    x = Edges[i].dest;
                    y = Edges[i].source;
                }
            }
        }

        if (x != -1 && y != -1) {
            printf("\nIteration %d:\n", edge + 1);
            printf("Selected Edge: (%d, %d) cost: %d\n", x, y, min);
            mincost += min;
            selected[y - 1] = 1;
            edge++;
            printVicinity(n, selected, costs);
        }
    }

    printf("\nMinimum cost = %d\n", mincost);
}

int main() {
    int n = 8;

    struct Edge Edges[] = {
        {1, 2, 1}, {1, 3, 2}, {2, 3, 1}, {2, 6, 1}, {2, 5, 2}, {2, 8, 3},
        {3, 4, 3}, {3, 5, 2}, {3, 6, 2}, {4, 6, 2}, {5, 6, 3}, {5, 8, 1},
        {6, 7, 1}, {7, 5, 2}, {8, 5, 1}
    };

    int numEdges = sizeof(Edges) / sizeof(Edges[0]);

    Prim(Edges, numEdges, n);

    return 0;
}
