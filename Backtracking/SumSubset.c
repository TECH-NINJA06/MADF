#include <stdio.h>
#include <stdlib.h>

int n,m;
int w[100],x[100];
void print(int k) {
    printf("[");
    for (int i = 0; i <=k; i++) {
        if (x[i] == 1) 
            printf("%d ", w[i]);
    }
    printf("]\n");
}
void SumOfSub(int s, int k, int r){
    x[k]=1;
    if(s+w[k]==m){
        print(k);
    }
    else if(s+w[k]+w[k+1]<=m)
        SumOfSub(s+w[k],k+1,r-w[k]);
    if(s+r-w[k]>=m && s+w[k+1]<=m){
        x[k]=0;
        SumOfSub(s,k+1,r-w[k]);
    }
}
int main(){
    int r = 0;
    printf("Enter size of set:");
    scanf("%d",&n);
    printf("Enter elements of set:");
    for(int i=0;i<n;i++){
        scanf("%d",&w[i]);
        r+=w[i];
    }
    for(int i=0;i<n;i++){
        x[i]=0;
    }
    printf("Enter sum:");
    scanf("%d",&m);
    printf("Subsets are:\n");
    SumOfSub(0,0,r);
}