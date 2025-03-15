#include <stdio.h>
#include <time.h>

#define INF 1e9
#define MAX_VERTICES 100   

int numVertices, numStages;
double cost[MAX_VERTICES][MAX_VERTICES], minCost[MAX_VERTICES];
int nextVertex[MAX_VERTICES], prevVertex[MAX_VERTICES], path[MAX_VERTICES];
int stage[MAX_VERTICES];

struct Edge {
    int start, end, weight;
};

struct Edge edges[] = {
    {1,2,13},{1,3,11},{1,4,12},{1,5,10},
    {2,6,7},{2,7,8},{2,8,6},  {3,6,7},{3,8,6},{3,9,8},  {4,6,8},{4,7,6},{4,9,7},  {5,6,6},{5,7,8},{5,8,7},
    {6,10,11},{6,11,12},{6,13,13},  {7,10,13},{7,11,11},{7,12,12},  {8,11,12},{8,12,11},{8,13,13},  {9,10,13},{9,12,12},{9,13,11},
    {10,14,10},{11,14,12},{12,14,13},{13,14,11}
};


void setStages() {
    for(int i = 1; i <= numVertices; i++) {
        stage[i] = INF;
    }
    stage[1] = 1;
    for(int i = 2; i <= numVertices; i++) {
        for(int j = 1; j <= i; j++) {
            if(stage[j] < stage[i]) {
                for(int k = 0; k < 32; k++) {
                    if(edges[k].start == j && edges[k].end == i) {
                        stage[i] = stage[j] + 1;
                        break;
                    }
                }
            }
        }
    }
}

void FGraph() {
    setStages();
    minCost[numVertices] = 0.0;
    printf("cost[%d, %d] = %.2f\n",stage[numVertices], numVertices, minCost[numVertices]);
    
    for (int j = numVertices - 1; j >= 1; j--) {
        minCost[j] = INF;
        for (int r = j + 1; r <= numVertices; r++) {
            double totalCost = cost[j][r] + minCost[r];
            if (cost[j][r] < INF && totalCost < minCost[j]) {
                minCost[j] = totalCost;
                nextVertex[j] = r;
            }
        }
        if (minCost[j] < INF) {
            printf("cost[%d, %d] = %.2f  d(%d) = %2d\n",stage[j], j, minCost[j],j,nextVertex[j]);
        }
    }

    path[1] = 1;
    path[numStages] = numVertices;
    for (int j = 2; j < numStages; j++) {
        path[j] = nextVertex[path[j - 1]];
    }
}

void BGraph() {
    minCost[1] = 0.0;
    printf("cost[%d, %d] = %.2f\n",1, 1, minCost[1]);
    
    for (int j = 2; j <= numVertices; j++) {
        minCost[j] = INF;
        for (int r = 1; r < j; r++) {
            double totalCost = cost[r][j] + minCost[r];
            if (cost[r][j] < INF && totalCost < minCost[j]) {
                minCost[j] = totalCost;
                prevVertex[j] = r;
            }
        }
        if (minCost[j] < INF) {
            printf("cost[%d, %d] = %.2f  d(%d) = %2d\n", stage[j], j, minCost[j], j, nextVertex[j]);
        }
    }

    path[1] = 1;  
    path[numStages] = numVertices;
    
    int current = numVertices;
    for (int i = numStages; i > 1; i--) {
        current = prevVertex[current];
        path[i-1] = current;
    }
}

void displayPath() {
    printf("Shortest Path: ");
    for (int i = 1; i <= numStages; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
}

int main() {
    numVertices = 14;
    numStages = 5;
    clock_t start, end; 
    double time_taken;
    
    for (int i = 1; i <= numVertices; i++) {
        for (int j = 1; j <= numVertices; j++) {
            cost[i][j] = INF;
        }
    }
    
    for(int i = 0; i < 32; i++) {
        cost[edges[i].start][edges[i].end] = edges[i].weight;
    }

    printf("Forward Graph\n");   
    FGraph();
    displayPath();

    printf("\nBackward Graph\n");
    start = clock();
    BGraph();
    end = clock();
    time_taken = (((double)(end - start))/CLOCKS_PER_SEC)*1000;
    displayPath();
    printf("\nExecution Time: %.6f ms\n", time_taken); 
    
    return 0;
}