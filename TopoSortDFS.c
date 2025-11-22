#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Stack {
    int* arr;
    int top;
    int size;
}Stack;

void initStack(Stack* st , int size) {
    st->arr = (int*)malloc(size*sizeof(int));
    for(int i = 0 ; i<size ; i++) {
        st->arr[i] = -1;
    }
    st->size = size;
    st->top = -1;
}

void push(Stack* st , int x) {
    if(st->top == st->size - 1) return;
    (st->top)++;
    st->arr[st->top] = x;
}

int pop(Stack* st) {
    if(st->top == -1) return -1;
    int value = st->arr[st->top];
    (st->top)--;
    return value;
}

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** neighbours;
} Graph;

void initGraph(Graph* g, int V) {
    g->V = V;
    g->neighbours = (Node**)malloc(V * sizeof(Node*));
    for(int i = 0; i < V; i++) {
        g->neighbours[i] = NULL;
    }
}

void buildGraph(int** edges, int E, int V, Graph* g) {
    for(int i = 0; i < E; i++) {
        int src = edges[i][0];
        int dest = edges[i][1];
        
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = dest;
        newNode->next = g->neighbours[src];
        g->neighbours[src] = newNode;
    }
}

void topoSort(Stack* st , bool* visited , Graph* g , int node) {
    int V = g->V;
    visited[node] = true;
    Node* head = g->neighbours[node];
    while(head) {
        if(!visited[head->data]) {
            topoSort(st , visited , g, head->data);
        }
        head = head->next;
    }
    push(st , node);
}

int main() {
    int V, E;
    printf("Please enter the number of vertices and edges of directed graph : ");
    if(scanf("%d%d", &V, &E) != 2) return 1;
    
    int** edges = (int**)malloc(E * sizeof(int*));
    for(int i = 0; i < E; i++) {
        edges[i] = (int*)malloc(2 * sizeof(int));
    }
    
    for(int i = 0; i < E; i++) {
        printf("Please enter the edge in (src,dest) format : ");
        scanf("%d%d", &edges[i][0], &edges[i][1]);
    }
    
    Graph g;
    initGraph(&g, V);
    buildGraph(edges, E, V, &g);

    Stack st;
    initStack(&st , V*V);

    bool* visited = (bool*)malloc(V*sizeof(bool));
    for(int i = 0 ; i<V ; i++) visited[i] = false;

    for(int i = 0 ; i<V ; i++) {
        if(!visited[i]) topoSort(&st , visited , &g , i);
    }

    int *answer = st.arr;
    int start = 0;
    int end = st.top;

    while(start <= end) {
        int temp = answer[start];
        answer[start] = answer[end];
        answer[end] = temp;
        start++;
        end--; 
    }

    for(int i = 0 ; i<V ; i++) {
        printf("%d " , answer[i]); 
    }
    printf("\n");
}