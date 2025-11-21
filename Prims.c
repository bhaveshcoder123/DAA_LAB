#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
    int data;
    int weight;
    struct Node* next;
}Node;

typedef struct Graph {
    int vertices;
    Node** neighbours;
}Graph;

void initGraph(Graph* g, int vertices) {
    g->vertices = vertices;
    g->neighbours = (Node**)malloc(vertices * sizeof(Node*));
    for(int i = 0; i < vertices; i++) g->neighbours[i] = NULL;
}

void inputGraph(Graph* g) {
    int edges;
    printf("Please enter the number of edges in the graph : ");
    scanf("%d", &edges);
    
    for(int i = 0; i < edges; i++) {
        int source, dest, wt;
        printf("Please enter the source , destination and weight of the edge : ");
        scanf("%d%d%d", &source, &dest, &wt);
        
        
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;
        newNode->data = dest;
        newNode->weight = wt;
        
        Node* head = g->neighbours[source];
        newNode->next = head;
        g->neighbours[source] = newNode;
        
       
        newNode = (Node*)malloc(sizeof(Node));
        newNode->next = NULL;
        newNode->data = source;
        newNode->weight = wt;
        
        head = g->neighbours[dest];
        newNode->next = head;
        g->neighbours[dest] = newNode;
    }
}

void printGraph(Graph* g) {
    int V = g->vertices;
    for(int i = 0; i < V; i++) {
        Node* head = g->neighbours[i];
        printf("%d -> ", i);
        while(head) {
            printf("(%d , %d) ", head->data, head->weight);
            head = head->next;
        }
        printf("\n");
    }
}

typedef struct Edge {
    int source;
    int destination;
    int weight;
} Edge;

typedef struct MinHeap {
    Edge* arr;
    int currSize;
    int size;
} MinHeap;

void initHeap(MinHeap* mh, int size) {
    mh->size = size;
    mh->arr = (Edge*)malloc(size * sizeof(Edge));
    mh->currSize = 0;
}

void push(MinHeap* mh, Edge edge) {
    if(mh->currSize == mh->size) return;
    mh->arr[mh->currSize++] = edge;
    int index = mh->currSize - 1;
    while(index > 0) {
        int parent = (index - 1) / 2;
        if((mh->arr[parent]).weight > (mh->arr[index]).weight) {
            Edge temp = mh->arr[parent];
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
    
    if(left < mh->currSize && mh->arr[smallest].weight > mh->arr[left].weight) smallest = left;
    if(right < mh->currSize && mh->arr[smallest].weight > mh->arr[right].weight) smallest = right;
    
    if(smallest == index) return;
    
    Edge temp = mh->arr[smallest];
    mh->arr[smallest] = mh->arr[index];
    mh->arr[index] = temp;
    
    heapify(mh, smallest);
}

Edge pop(MinHeap* mh) {
    if(mh->currSize == 0) {
        Edge dummy;
        dummy.source = -1;
        dummy.weight = -1;
        dummy.destination = -1;
        return dummy;
    }
    Edge to_return = mh->arr[0];
    
    int index = --(mh->currSize);
    Edge temp = mh->arr[0];
    mh->arr[0] = mh->arr[index];
    mh->arr[index] = temp;
    
    heapify(mh, 0);
    
    return to_return;
}

int main() {
    int vertices;
    printf("Please enter the number of vertices in a graph : ");
    scanf("%d", &vertices);
    
    Graph g;
    initGraph(&g, vertices);
    
    inputGraph(&g);
    printf("\n\n");
    
    MinHeap mh;
    initHeap(&mh, vertices * vertices); 
    
    bool* visited = (bool*)malloc(vertices * sizeof(bool));
    int* parent = (int*)malloc(vertices * sizeof(int));
    int cost = 0;
    
    for(int i = 0; i < vertices; i++) {
        visited[i] = false;
        parent[i] = -1;
    }
   
    visited[0] = true;
    Node* head = g.neighbours[0];
    while(head) {
        Edge edge;
        edge.source = 0;
        edge.destination = head->data;
        edge.weight = head->weight;
        push(&mh, edge);
        head = head->next;
    }
    
    while(mh.currSize != 0) {
        Edge edge = pop(&mh);
        
        if(visited[edge.destination]) continue;
        
        visited[edge.destination] = true;
        cost += edge.weight;
        parent[edge.destination] = edge.source;
        
        int newSource = edge.destination;
        Node* head = g.neighbours[edge.destination];
        while(head) {
            if(!visited[head->data]) { 
                Edge newEdge;
                newEdge.source = newSource;
                newEdge.destination = head->data;
                newEdge.weight = head->weight;
                push(&mh, newEdge);
            }
            head = head->next;
        }
    }

    printf("MST Structure (Node -> Parent):\n");
    for(int i = 0; i < vertices; i++) {
        if(parent[i] != -1) {
            printf("%d -> %d\n", i, parent[i]);
        }
    }
    
    printf("\nThe cost of building the MST is : %d .\n", cost);
    
    return 0;
}