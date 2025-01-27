#include <stdio.h>
struct Student{
    int roll,age;
    char name[20];
};
void interchange(struct Student *a, struct Student *b){
    struct Student temp = *a;
    *a = *b;
    *b = temp;
}
int partition(struct Student a[], int m, int p){
    int v = a[m].age;
    int i = m + 1;
    int j = p - 1;

    printf("[ ");
    for(int k = i; k < j; k++)
        printf("%d ", a[k].age);
    printf("]  \n");
    // printf("i=%d j=%d\n",i,j);   
    while (i <= j){
        while (i <= j && a[i].age <= v)
            i = i + 1;
        while (i <= j && a[j].age >= v)
            j = j - 1;
        if (i < j)
            interchange(&a[i], &a[j]);
        // printf("[ ");
        // for(int k = 0; k < 9; k++)
        //     printf("%d ", a[k].age);
        // printf("]  ");
        // printf("i=%d j=%d\n",i,j);    
    }
    interchange(&a[m], &a[j]);
    printf("[ ");
    for(int k = 0; k < 9; k++)
        printf("%d ", a[k].age);
    printf("]  ");
    printf("j=%d\n",j);    
    return j;
}
void quickSort(struct Student a[], int p, int q){
    if (p < q) {
        int j = partition(a, p, q + 1);
        quickSort(a, p, j - 1);
        quickSort(a, j + 1, q);
    }
}

int main(){
    struct Student a[] = {{1, 19, "A"}, {2, 18, "B"}, {3, 20, "C"}, {4, 17, "D"}, {5, 21, "E"}, {6, 16, "F"}, {7, 22, "G"}, {8, 15, "H"}, {9, 23, "I"}};
    quickSort(a, 0, 9);
    for (int i = 0; i < 9; i++)
    {
        printf("%d %d %s\n", a[i].roll, a[i].age, a[i].name);
    }
    return 0;
}