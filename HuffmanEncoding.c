#include<stdio.h>
#include<stdlib.h>
#define MAX 100

/*
Given a string S of distinct character of size N and their corresponding frequency f[ ] i.e. character S[i] has f[i] frequency. Your task is to build the Huffman tree print all the huffman codes in preorder traversal of the tree.

S = "abcdef"
f[] = {5, 9, 12, 13, 16, 45}

HuffmanCodes will be:
f : 0
c : 100
d : 101
a : 1100
b : 1101
e : 111
*/

typedef struct Node {
    char c;
    int data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct MinHeap {
    Node** arr;
    int currSize;
    int size;
} MinHeap;

void initHeap(MinHeap* mh, int size) {
    mh->size = size;
    mh->arr = (Node**)malloc(size * sizeof(Node*));
    for(int i = 0 ; i<size ; i++) mh->arr[i] = NULL;
    mh->currSize = 0;
}

void push(MinHeap* mh, Node* node) {
    if(mh->currSize == mh->size) return;
    mh->arr[mh->currSize++] = node;
    int index = mh->currSize - 1;
    while(index > 0) {
        int parent = (index - 1) / 2;
        if((mh->arr[parent])->data > (mh->arr[index])->data) {
            Node* temp = mh->arr[parent];
            mh->arr[parent] = mh->arr[index];
            mh->arr[index] = temp;
            index = parent;
        }
        else break;
    }
}

void heapify(MinHeap* mh, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if(left < mh->currSize && mh->arr[smallest]->data > mh->arr[left]->data) smallest = left;
    if(right < mh->currSize && mh->arr[smallest]->data > mh->arr[right]->data) smallest = right;
    
    if(smallest == index) return;
    
    Node* temp = mh->arr[smallest];
    mh->arr[smallest] = mh->arr[index];
    mh->arr[index] = temp;
    
    heapify(mh, smallest);
}

Node* pop(MinHeap* mh) {
    if(mh->currSize == 0) return NULL;
    Node* to_return = mh->arr[0];
    
    int index = --(mh->currSize);
    Node* temp = mh->arr[0];
    mh->arr[0] = mh->arr[index];
    mh->arr[index] = temp;
    
    heapify(mh, 0);
    
    return to_return;
}

MinHeap* buildHeap(Node** nodes , int N) {
    MinHeap* mh = (MinHeap*)malloc(sizeof(MinHeap));
    mh->arr = nodes;
    mh->size = N;
    mh->currSize = N;

    for(int i = N/2 - 1; i>=0 ; i--) {
        heapify(mh , i);
    }
    return mh;
}

void preOrderPrint(Node* root , int index , char* code) {
    if(!root) return;
    char* str = (char*)malloc((index + 1)*sizeof(char));
    for(int i = 0 ; i<index ; i++) {
        str[i] = code[i];
    }
    str[index] = '\0';
    if(root->c != '\0') printf("%c -> %s\n" , root->c , str);
    code[index] = '0';
    preOrderPrint(root->left , index + 1 , code);
    code[index] = '1';
    preOrderPrint(root->right , index + 1 , code);
}

void huffmanEncoding(char* S , int* f , int N) {
    Node** nodes = (Node**)malloc(N*sizeof(Node*));

    for(int i = 0 ; i<N ; i++) {
        Node* node = (Node*)malloc(sizeof(Node));
        node->c = S[i];
        node->data = f[i];
        node->left = NULL;
        node->right = NULL;

        nodes[i] = node;
    }

    MinHeap* mh = buildHeap(nodes , N);

    while(mh->currSize > 1) {
        Node* first = pop(mh);
        Node* second = pop(mh);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = first->data + second->data;
        newNode->c = '\0';
        newNode->left = first;
        newNode->right = second;

        push(mh , newNode);
    }

    Node* root = pop(mh);
    char* code = (char*)malloc(MAX*sizeof(char));
    preOrderPrint(root , 0 , code);
}

int main() {
    int N;
    printf("Please enter the value of N : ");
    scanf("%d" , &N);

    getchar();
    printf("Please enter the string S : ");
    char* S = (char*)malloc((N+1)*sizeof(char));
    scanf("%[^\n]s" , S);

    int* f = (int*)malloc(N*sizeof(int));
    printf("Please enter the f array : ");
    for(int i = 0 ; i<N ; i++) {
        scanf("%d" , &f[i]);
    }

    huffmanEncoding(S , f , N);
}