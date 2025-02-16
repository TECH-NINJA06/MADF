#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Edge {
    int startVertex, endVertex, weight;
};

struct MinHeap {
    struct Edge edges[MAX];
    int size;
};

int parent[MAX];

void heapify(struct MinHeap *heap, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;
    if (leftChild < heap->size && heap->edges[leftChild].weight < heap->edges[smallest].weight)
        smallest = leftChild;
    if (rightChild < heap->size && heap->edges[rightChild].weight < heap->edges[smallest].weight)
        smallest = rightChild;
    if (smallest != index) {
        struct Edge temp = heap->edges[index];
        heap->edges[index] = heap->edges[smallest];
        heap->edges[smallest] = temp;
        heapify(heap, smallest);
    }
}

struct Edge Delete(struct MinHeap *heap) {
    struct Edge minEdge = heap->edges[0];
    heap->edges[0] = heap->edges[--heap->size];
    heapify(heap, 0);
    return minEdge;
}

void buildHeap(struct MinHeap *heap) {
    for (int i = heap->size / 2 - 1; i >= 0; i--)
        heapify(heap, i);
}

int Find(int vertex) {
    while(parent[vertex]>=0)
        vertex = parent[vertex];
    return vertex;
}

void Union(int vertex1, int vertex2) {
    int root1 = Find(vertex1);
    int root2 = Find(vertex2);
    if (root1 != root2) {
        parent[root1] = root2;
    }
}

void printParentArray(int numVertices) {
    printf("Parent array: ");
    for (int i = 0; i < numVertices; i++)
        printf("%d ", parent[i]);
    printf("\n");
}

void kruskal(struct Edge edges[], int numVertices, int numEdges) {
    struct MinHeap heap;
    heap.size = numEdges;
    for (int i = 0; i < numEdges; i++)
        heap.edges[i] = edges[i];
    
    buildHeap(&heap);
    
    for (int i = 0; i < numVertices; i++)
        parent[i] = -1;
    
    struct Edge result[MAX];
    int minCost = 0, edgeCount = 0;
    while (edgeCount < numVertices - 1 && heap.size > 0) {
        struct Edge edge = Delete(&heap);
        int startParent = Find(edge.startVertex);
        int endParent = Find(edge.endVertex);
        
        if (startParent != endParent) {
            result[edgeCount] = edge;
            printf("Edge selected: %d - %d | Cost: %d\n", edge.startVertex, edge.endVertex, edge.weight);
            minCost += edge.weight;
            Union(startParent, endParent);
            edgeCount++;
            printf("MinCost=%d\n", minCost);
            printParentArray(numVertices);
            printf("\n");
        }
    }
    if (edgeCount != numVertices - 1)
        printf("No spanning tree exists\n");
    else {
        printf("Edges in the Minimum Spanning Tree:\n");
        for (int i = 0; i < edgeCount; i++)
            printf("%d - %d | Cost: %d\n", result[i].startVertex+1, result[i].endVertex+1, result[i].weight);
        printf("Minimum Cost: %d\n", minCost);
    }
}

int main() {
    int numVertices, numEdges;
    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);
    
    struct Edge edges[MAX];
    printf("Enter edges (startVertex endVertex weight):\n");
    for (int i = 0; i < numEdges; i++) {
        scanf("%d %d %d", &edges[i].startVertex, &edges[i].endVertex, &edges[i].weight);
        edges[i].startVertex--;
        edges[i].endVertex--;  
    }
    
    kruskal(edges, numVertices, numEdges);
    return 0;
}