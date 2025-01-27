#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item
typedef struct {
    int index;
    float profit;
    float weight;
    float ratio;
} Item;

// Function to compare items based on profit/weight ratio
int compareItems(const void *a, const void *b) {
    Item *itemA = (Item *)a;
    Item *itemB = (Item *)b;
    if (itemA->ratio < itemB->ratio) return 1;
    if (itemA->ratio > itemB->ratio) return -1;
    return 0;
}

void greedyKnapsack(int n, float m, Item items[]) {
    float solution[n];  // Solution vector
    float totalProfit = 0.0;  // Total profit
    float remainingCapacity = m;
    
    // Initialize solution vector
    for (int i = 0; i < n; i++) {
        solution[i] = 0.0;
    }

    // Sort items by profit/weight ratio
    qsort(items, n, sizeof(Item), compareItems);

    // Greedy selection of items
    for (int i = 0; i < n; i++) {
        if (items[i].weight > remainingCapacity) {
            break;  // If the item can't fit, stop
        }
        solution[items[i].index] = 1.0;  // Include the item fully
        remainingCapacity -= items[i].weight;
        totalProfit += items[i].profit;
    }

    // If there is some remaining capacity, include a fraction of the next item
    for (int i = 0; i < n; i++) {
        if (solution[items[i].index] == 0.0 && remainingCapacity > 0) {
            float fraction = remainingCapacity / items[i].weight;
            solution[items[i].index] = fraction;
            totalProfit += items[i].profit * fraction;
            remainingCapacity = 0;  // Knapsack is full
        }
    }

    // Print solution
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
