#include<stdio.h>
#include<stdlib.h>
#define INF 1000000000000000000LL

typedef long long ll;

typedef struct Node {
    int data;
    int weight;
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
        int weight = edges[i][2];
        
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->data = dest;
        newNode->weight = weight;
        newNode->next = g->neighbours[src];
        g->neighbours[src] = newNode;
        
        newNode = (Node*)malloc(sizeof(Node));
        newNode->data = src;
        newNode->weight = weight;
        newNode->next = g->neighbours[dest];
        g->neighbours[dest] = newNode;
    }
}

typedef struct Edge {
    int source;
    ll weight;
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

ll* dijkstraAlgo(Graph* g , int src) {
    int V = g->V;
    ll* dist = (ll*)malloc(V*sizeof(ll));
    for(int i = 0 ; i<V ; i++) dist[i] = INF;

    MinHeap mh;
    initHeap(&mh , V*V);

    dist[src] = 0;
    Edge edge;
    edge.source = src;
    edge.weight = 0;
    push(&mh , edge);

    while(mh.currSize > 0) {
        edge = pop(&mh);
        if(edge.weight > dist[edge.source]) continue;
        
        Node* head = g->neighbours[edge.source];
        while(head) {
            if(dist[edge.source] + head->weight < dist[head->data]) {
                dist[head->data] = dist[edge.source] + head->weight;
                Edge newEdge;
                newEdge.source = head->data;
                newEdge.weight = dist[head->data];
                push(&mh , newEdge);
            }
            head = head->next;
        }
    }

    return dist;
}

int main() {
    int V, E;
    printf("Please enter the number of vertices and edges of undirected graph : ");
    if(scanf("%d%d", &V, &E) != 2) return 1;
    
    int** edges = (int**)malloc(E * sizeof(int*));
    for(int i = 0; i < E; i++) {
        edges[i] = (int*)malloc(3 * sizeof(int));
    }
    
    for(int i = 0; i < E; i++) {
        printf("Please enter the edge in (src,dest,weight) format : ");
        scanf("%d%d%d", &edges[i][0], &edges[i][1] , &edges[i][2]);
    }
    
    Graph g;
    initGraph(&g, V);
    buildGraph(edges, E, V, &g);

    printf("Please enter the source for dijkstra algo : ");
    int src;
    scanf("%d" , &src);
    ll* dist = dijkstraAlgo(&g , src);

    for(int i = 0 ; i<V ; i++) {
        printf("%d -> %lld\n" , i , dist[i]);
    }

}