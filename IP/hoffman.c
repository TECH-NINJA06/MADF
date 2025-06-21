#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

typedef struct Node {
    char ch;
    int freq;
    struct Node *left, *right;
} Node;

typedef struct {
    Node *data[MAX];
    int size;
} PQ;

int freq[MAX] = {0};

Node *createNode(char ch, int freq) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->ch = ch;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

void initQueue(PQ *q) { q->size = 0; }

void insertQ(PQ *q, Node *node) {
    int i = q->size++;
    while (i > 0 && q->data[(i - 1) / 2]->freq > node->freq) {
        q->data[i] = q->data[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    q->data[i] = node;
}

Node *removeMin(PQ *q) {
    Node *min = q->data[0];
    Node *last = q->data[--q->size];
    int i = 0, child;
    while (i * 2 + 1 < q->size) {
        child = i * 2 + 1;
        if (child + 1 < q->size && q->data[child + 1]->freq < q->data[child]->freq)
            child++;
        if (last->freq <= q->data[child]->freq)
            break;
        q->data[i] = q->data[child];
        i = child;
    }
    q->data[i] = last;
    return min;
}

Node *buildHuffmanTree(char *str) {
    PQ q;
    initQueue(&q);
    for (int i = 0; str[i]; i++)
        freq[(unsigned char)str[i]]++;

    for (int i = 0; i < MAX; i++)
        if (freq[i] > 0)
            insertQ(&q, createNode((char)i, freq[i]));

    while (q.size > 1) {
        Node *t1 = removeMin(&q);
        Node *t2 = removeMin(&q);
        Node *newNode = createNode('\0', t1->freq + t2->freq);
        newNode->left = t1;
        newNode->right = t2;
        insertQ(&q, newNode);
    }
    return removeMin(&q);
}

void encoding(Node *root, char *code, int depth, char codes[MAX][MAX]) {
    if (!root)
        return;
    if (!root->left && !root->right) {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
        return;
    }
    code[depth] = '0';
    encoding(root->left, code, depth + 1, codes);
    code[depth] = '1';
    encoding(root->right, code, depth + 1, codes);
}

int main() {
    char str[1000], codes[MAX][MAX] = {{0}}, buffer[MAX];
    scanf("%[^\n]", str);
    Node* root = buildHuffmanTree(str);
    encoding(root, buffer, 0, codes);

    printf("Character  | Frequency  | Code\n");
    printf("-------------------------------\n");
    for (int i = 0; i < MAX; i++) {
        if (freq[i] > 0) {
            if (i == ' ')
                printf("space      ");
            else if (i == '\n')
                printf("\\n         ");
            else if (i == '\t')
                printf("\\t         ");
            else
                printf("'%c'        ", i);

            printf("| %-10d | %s\n", freq[i], codes[i]);
        }
    }
    return 0;
}
