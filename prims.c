#include<stdio.h>
#include<stdlib.h>

typedef struct pair
{
    int first;
    int second;
    int third;
}pair;

typedef struct Heap
{
    pair* arr;
    int size;
}Heap;

Heap* init()
{
    Heap* hp = (Heap*) malloc(sizeof(Heap));
    hp->size = 0;
    hp->arr = (pair*) malloc(100 * sizeof(pair));

    return hp;
}

void insert(Heap* hp , pair data)
{   
    int i = hp->size;
    hp->size++;

    hp->arr[i] = data;

    while(i > 0 && hp->arr[(i-1)/2].first > hp->arr[i].first)
    {
        pair temp = hp->arr[(i-1)/2];
        hp->arr[(i-1)/2] = hp->arr[i];
        hp->arr[i] = temp;

        i = (i-1)/2;
    }
}

int isEmpty(Heap* hp)
{
    return hp->size == 0;
}

void Heapify(Heap* hp , int i)
{
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < hp->size && hp->arr[left].first < hp->arr[i].first) smallest = left;
    if(right < hp->size && hp->arr[right].first < hp->arr[i].first) smallest = right;

    if(i != smallest)
    {
        pair temp = hp->arr[i];
        hp->arr[i] = hp->arr[smallest];
        hp->arr[smallest] = temp;

        Heapify(hp , smallest);
    }
}

void pop(Heap* hp)
{
    hp->arr[0] = hp->arr[(hp->size)-1];
    hp->size--;
    Heapify(hp , 0);
}

pair getMin(Heap* hp)
{
    return hp->arr[0];
}

typedef struct Node
{
    int data;
    int weight;
    struct Node* next;
}Node;

typedef struct Graph
{
    int V;
    Node** list;
}Graph;

Graph* initGraph(int v)
{
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->V = v;
    graph->list = (Node**) malloc(v*sizeof(Node*));

    for(int i = 0 ; i < v ; i++)
    graph->list[i] = NULL;

    return graph;
}

void insertinGraph(Graph* gp , int source , int destination ,int weight)
{   
    Node* node = (Node*) malloc(sizeof(Node));
    node->data = destination;
    node->weight = weight;
    node->next = NULL;
    if(!gp->list[source])
    gp->list[source] = node;
    else 
    {   
        node->next = gp->list[source];
        gp->list[source] = node;
    }
    
    return;
}

void printMst(int* arr , int V)
{   
    printf("Your Mst Looks like : ");
    for(int i= 0 ; i < V ; i++)
    printf("%d " , arr[i]);
}

void prims(Graph* gp , int V)
{
    int* arr = (int*) malloc(V* sizeof(int));
    int* visited = (int*) malloc(V*sizeof(int));
    int* cost = (int*) malloc(V*sizeof(int));

    for(int i= 0 ; i < V ; i++)
    cost[i] = 10000;

    for(int i = 0 ; i < V ; i++)
    visited[i] = 0;

    Heap* hp = init();
    pair p;
    p.first = 0;
    p.second = -1;
    p.third = 0;

    insert(hp , p);
    cost[0] = 0;

    while(!isEmpty(hp))
    {
        pair p = getMin(hp);
        int weight = p.first;
        int parent = p.second;
        int node = p.third;
        
        pop(hp);
        if(visited[node]) continue;

        visited[node] = 1;
        arr[node] = parent;

        Node* n = gp->list[node];
        while(n)
        {
            if(!visited[n->data] && n->weight < cost[n->data])
            {   
                pair p;
                p.first = n->weight;
                p.second = node;
                p.third = n->data;
                insert(hp , p);
                cost[n->data] = n->weight;
            }
            n = n->next;                                                                    
        }
    }

    printMst(arr , V);

    int Totalcost = 0;
    for(int i = 0 ; i < V ; i++)
    Totalcost+=cost[i];

    printf("Your total Cost is : %d" , Totalcost);
}

int main()
{   
    int V;
    printf("Enter the number of vertices : ");
    scanf("%d" , &V);
    Graph* gp = initGraph(V);

    int edges;
    printf("Enter the number of edges : ");
    scanf("%d",&edges);

    for(int i = 0 ; i < edges ; i++)
    {
        int source;
        int destination;
        int weight;

        printf("Enter the source : ");
        scanf("%d",&source);

        printf("Enter the destination : ");
        scanf("%d",&destination);

        printf("Enter the weight : ");
        scanf("%d" , &weight);

        insertinGraph(gp , source , destination , weight);
        insertinGraph(gp ,  destination,source  , weight);
    }

    prims(gp , V);
}