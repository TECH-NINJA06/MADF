#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#define MAX 30

struct Edges {
    int ori, dest;
};

int max_edges, n, count = 0;
int t[MAX][2], near[MAX], cost[MAX][MAX];
struct Edges E[MAX];

int prims(struct Edges E[MAX], int cost[MAX][MAX], int n, int t[MAX][2]) {
    int i, k, l, j, m, index, o, d;
    int mincost = INT_MAX;
    
    for (i = 1; i <= count; i++) {
        o = E[i].ori;
        d = E[i].dest;
        if (cost[o][d] < mincost || (cost[o][d] == mincost && o < k)) {
            mincost = cost[o][d];
            k = o;
            l = d;
        }
    }
    
    t[0][0] = k;
    t[0][1] = l;
    
    for (i = 1; i <= n; i++) {
        near[i] = (cost[i][l] < cost[i][k]) ? l : k;
    }
    near[k] = 0;
    near[l] = 0;
    
    printf("%17s%18s\n", "near[j]", "cost[j,near[j]]");
    for (i = 1; i <= n; i++) {
        if (near[i] == 0)
            printf("near[%d]       %-13d%s\n", i, near[i], "-");  
        else if (cost[i][near[i]] == INT_MAX)  
            printf("near[%d]       %-13d%s\n", i, near[i], "inf");  
        else  
            printf("near[%d]       %-13d%d\n", i, near[i], cost[i][near[i]]);
    }
    
    printf("Mincost= %d\n", mincost);
    
    for (i = 2; i <= n - 1; i++) {
        m = INT_MAX;
        for (j = 1; j <= n; j++) {
            if (near[j] != 0 && (cost[j][near[j]] < m || (cost[j][near[j]] == m && j < index))) {
                index = j;
                m = cost[j][near[j]];
            }
        }
        
        t[i - 1][0] = index;
        t[i - 1][1] = near[index];
        mincost += m;
        near[index] = 0;
        
        for (k = 1; k <= n; k++) {
            if (near[k] != 0 && cost[k][near[k]] > cost[k][index])
                near[k] = index;
        }
        
        printf("\n%17s%18s\n", "near[j]", "cost[j,near[j]]");
        for (int z = 1; z <= n; z++) {
            if (near[z] == 0)
                printf("near[%d]       %-13d%s\n", z, near[z], "-");
            else if (cost[z][near[z]] == INT_MAX)
                printf("near[%d]       %-13d%s\n", z, near[z], "inf");
            else
                printf("near[%d]       %-13d%d\n", z, near[z], cost[z][near[z]]);
        }
        printf("Mincost= %d\n", mincost);
    }
    return mincost;
}

void create_graph() {
    int origin, destin;
    printf("Enter the number of vertices: ");
    scanf("%d", &n);
    max_edges = (n * (n - 1)) / 2;
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cost[i][j] = INT_MAX;
    }
    
    printf("Enter the edge (-1 -1 to quit) and enter cost: ");
    for (int i = 1; i <= max_edges; i++) {
        scanf("%d%d", &origin, &destin);
        if (origin == -1 && destin == -1)
            break;
        if (origin > n || destin > n || origin <= 0 || destin <= 0) {
            printf("Invalid vertex!\n");
            i--;
            continue;
        }
        scanf("%d", &cost[origin][destin]);
        cost[destin][origin] = cost[origin][destin];
        count++;
        E[i].ori = origin;
        E[i].dest = destin;
    }
}

int main() {
    int m;
    struct timeval start, end;
    long s, us;
    double t_ms, t_us;
    
    create_graph();
    gettimeofday(&start, NULL);
    m = prims(E, cost, n, t);
    gettimeofday(&end, NULL);
    
    s = end.tv_sec - start.tv_sec;
    us = end.tv_usec - start.tv_usec;
    t_us = s * 1000000 + us;
    t_ms = t_us / 1000.0;
    
    printf("\n\nt   1   2\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%-4d%-4d%d\n", i, t[i][0], t[i][1]);
    }
    printf("\nExecution time: %f milliseconds\n", t_ms);
    
    return 0;
}
