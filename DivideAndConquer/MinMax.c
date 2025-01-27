#include <stdio.h>
#include <string.h>

void MinMax(char a[][20], int i, int j, char *min, char *max){
    char min1[20], max1[20], min2[20], max2[20];
    int mid;
    if (i == j){
        strcpy(min, a[i]);
        strcpy(max, a[i]);
    }
    else if (i == j - 1){
        if (strcmp(a[i], a[j]) < 0){
            strcpy(min, a[i]);
            strcpy(max, a[j]);
        }
        else{
            strcpy(min, a[j]);
            strcpy(max, a[i]);
        }
    }
    else{
        mid = (i + j) / 2;
        MinMax(a, i, mid, min1, max1);
        MinMax(a, mid + 1, j, min2, max2);
        if (strcmp(min1, min2) < 0)
            strcpy(min, min1);
        else
            strcpy(min, min2);
        if (strcmp(max1, max2) > 0)
            strcpy(max, max1);
        else
            strcpy(max, max2);
    }
    printf("low: %d, high: %d, min: %s, max: %s\n", i, j, min, max);
}

int main(){
    char a[9][20] = {"Apple", "Banana", "Mango", "Grapes", "Orange", "Pineapple", "Guava", "Papaya", "Kiwi"};   
    char min[20], max[20];
    MinMax(a, 0, 8, min, max);
    printf("\n\nMinimum element is %s\n", min);
    printf("Maximum element is %s\n", max);
}