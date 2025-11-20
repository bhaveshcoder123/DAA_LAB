#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int V;
    Node** neighbours;
} Graph;

typedef struct Queue {
    int* arr;
    int front;
    int rear;
    int totalSize;
} Queue;

void initQueue(Queue* q, int totalSize) {
    q->totalSize = totalSize;
    q->front = -1;
    q->rear = -1;
    q->arr = (int*)malloc(totalSize * sizeof(int));
}

int getSize(Queue* q) {
    if(q->front == -1) return 0;
    int totalSize = q->totalSize;
    return (q->rear - q->front + 1 + totalSize) % totalSize;
}

void push(Queue* q, int value) {
    if(getSize(q) == q->totalSize) return;
    int totalSize = q->totalSize;
    if(q->front == -1) q->front = 0;
    q->rear = (q->rear + 1) % totalSize;
    q->arr[q->rear] = value;
}

int pop(Queue* q) {
    if(getSize(q) == 0) return -1;
    int totalSize = q->totalSize;
    int value = q->arr[q->front];
    if(q->front == q->rear) {
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % totalSize;
    }
    return value;
}

void initGraph(Graph* g, int V) {
    g->V = V;
    g->neighbours = (Node**)malloc(V * sizeof(Node*));
    for(int i = 0; i < V; i++) {
        g->neighbours[i] = NULL;
    }
}

void dfs(Graph* g, bool* visited, int node) {
    visited[node] = true;
    Node* head = g->neighbours[node];
    while(head) {
        int neighbour = head->data;
        if(visited[neighbour] == false) {
            dfs(g, visited, neighbour);
        }
        head = head->next;
    }
}

bool isConnected(Graph* g) {
    int V = g->V;
    bool* visited = (bool*)malloc(V * sizeof(bool));
    for(int i = 0; i < V; i++) visited[i] = false;
    
    dfs(g, visited, 0);
    
    for(int i = 0; i < V; i++) {
        if(!visited[i]) return false;
    }
    return true;
}

bool dfsCycle(Graph* g, bool* visited, int node, int parent) {
    visited[node] = true;
    Node* head = g->neighbours[node];
    while(head) {
        int neighbour = head->data;
        if(visited[neighbour] == false) {
            if(dfsCycle(g, visited, neighbour, node)) return true;
        }
        else if (parent != neighbour) return true;
        head = head->next;
    }
    return false;
}

bool isCycle(Graph* g) {
    int V = g->V;
    bool* visited = (bool*)malloc(V * sizeof(bool));
    for(int i = 0; i < V; i++) visited[i] = false;

    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            if(dfsCycle(g, visited, i, -1)) return true;
        }
    }
    return false;
}

void buildGraph(int** edges, int E, int V, Graph* g) {
    for(int i = 0; i < E; i++) {
        int src = edges[i][0];
        int dest = edges[i][1];
        
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = dest;
        newNode->next = g->neighbours[src];
        g->neighbours[src] = newNode;
        
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = src;
        newNode->next = g->neighbours[dest];
        g->neighbours[dest] = newNode;
    }
}

void printGraph(Graph* g) {
    int V = g->V;
    for(int i = 0; i < V; i++) {
        Node* head = g->neighbours[i];
        while(head) {
            printf("%d ", head->data);
            head = head->next;
        }
        printf("\n");
    }
}

bool isBipartite(Graph* g) {
    int V = g->V;
    int* color = (int*)malloc(V * sizeof(int));
    for(int i = 0; i < V; i++) color[i] = -1;
    
    Queue q;
    initQueue(&q, V); 

    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            push(&q, i);
            color[i] = 0;
            while(getSize(&q) != 0) {
                int node = pop(&q);
                Node* head = g->neighbours[node];
                while(head) {
                    int neighbour = head->data;
                    if(color[neighbour] == -1) {
                        push(&q, neighbour);
                        color[neighbour] = 1 - color[node];
                    }
                    else if (color[neighbour] == color[node]) {
                        return false;
                    }
                    head = head->next;
                }
            }
        }
    }
    return true;
}

int main() {
    int V, E;
    printf("Please enter the number of vertices and edges of undirected graph : ");
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
    
    printGraph(&g);
    
    if(!isConnected(&g)) {
        printf("The graph is not connected.\n");
    }
    else printf("The graph is connected.\n");

    if(!isCycle(&g)) {
        printf("The graph doesn't have a cycle.\n");
    }
    else printf("The graph has a cycle.\n");

    if(!isBipartite(&g)) {
        printf("The graph is not bipartite.\n");
    }
    else printf("The graph is bipartite.\n");
    
    return 0;
}