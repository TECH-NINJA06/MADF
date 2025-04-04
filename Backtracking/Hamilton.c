#include <stdio.h>
#include <time.h> // Include time.h for measuring execution time
#define MAX 100
int x[MAX], n;
int G[MAX][MAX];

void NextValue(int k){
    while(1){
        x[k]=(x[k]+1)%(n+1);
        if(x[k]==0) return;
        int j;
        if(G[x[k-1]][x[k]]!=0){
            int valid = 1;
            for(int j=1; j<k; j++){
                if(x[j] == x[k]){
                    valid = 0;
                    break;
                }
            }
            if(valid && ((k < n) || (k == n && G[x[k]][x[0]] != 0))){
                return;
            }
        }
    }
}
void Hamiltonian(int k){
    while(1){
        NextValue(k);
        if(x[k]==0)return;
        if(k==n-1){
            for(int i=0; i<n; i++)
                printf("%d ", x[i]);
            printf("%d\n", x[0]); // Ensure the cycle ends at the starting vertex
        }
        else
            Hamiltonian(k+1);        
    }
}
int main(){
    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
        }
    }

    for (int i = 0; i < n; i++) {
        x[i] = 0;
    }

    x[0] = 1; 
    printf("Hamiltonian cycles are:\n");

    clock_t start_time = clock(); 
    Hamiltonian(1);
    clock_t end_time = clock(); 
    double time_taken = ((double)(end_time - start_time) / CLOCKS_PER_SEC) * 1000;
    printf("Execution time: %.2f ms\n", time_taken);

    return 0;
}