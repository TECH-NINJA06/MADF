#include <stdio.h>
#include <stdlib.h>

struct Item {
    int index;
    float profit;
    float weight;
    float ratio;
};

int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

void greedyKnapsack(int n, float m, Item items[]) {
    float solution[n];
    float totalProfit = 0.0; 
    float remainingCapacity = m;
    
    for (int i = 0; i < n; i++) {
        solution[i] = 0.0;
    }
    qsort(items, n, sizeof(Item), compareItems);

    for (int i = 0; i < n; i++) {
        if (items[i].weight > remainingCapacity) {
            break; 
        }
        solution[items[i].index] = 1.0; 
        remainingCapacity -= items[i].weight;
        totalProfit += items[i].profit;
    }

    for (int i = 0; i < n; i++) {
        if (solution[items[i].index] == 0.0 && remainingCapacity > 0) {
            float fraction = remainingCapacity / items[i].weight;
            solution[items[i].index] = fraction;
            totalProfit += items[i].profit * fraction;
            remainingCapacity = 0; 
        }
    }
    printf("Selected items (fractions):\n");
    for (int i = 0; i < n; i++) {
        printf("Item %d: %.2f\n", i + 1, solution[i]);
    }
    printf("Total profit: %.2f\n", totalProfit);
}

int main() {
    int n;
    float m;

    printf("Enter the number of items: ");
    scanf("%d", &n);

    printf("Enter the capacity of the knapsack: ");
    scanf("%f", &m);

    Item items[n];
    printf("Enter the profit and weight of each item:\n");
    for (int i = 0; i < n; i++) {
        items[i].index = i;
        printf("Item %d:\n", i + 1);
        printf("Profit: ");
        scanf("%f", &items[i].profit);
        printf("Weight: ");
        scanf("%f", &items[i].weight);
        items[i].ratio = items[i].profit / items[i].weight;
    }

    greedyKnapsack(n, m, items);

    return 0;
}
