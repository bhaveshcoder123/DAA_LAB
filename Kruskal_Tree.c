#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node {
    int index;
    int rank;
    struct Node* parent;
}Node;

typedef struct DSU {
    int vertices;
    Node** nodes;
}DSU;

void initDSU(DSU* dsu , int V) {
    dsu->vertices = V;
    dsu->nodes = (Node**)malloc(V*sizeof(Node*));
    for(int i = 0 ; i<V ; i++) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->index = i;
        newNode->rank = 1;
        newNode->parent = newNode;

        dsu->nodes[i] = newNode;
    }
}

int partition(int** edges , int start , int end) {
    int slow = start;
    int fast = start;

    while(fast <= end) {
        if(edges[fast][2] <= edges[end][2]) {
            int* temp = edges[fast];
            edges[fast] = edges[slow];
            edges[slow] = temp;
            slow++;
        }
        fast++;
    }

    return slow - 1;
}

void qS(int** edges , int start , int end) {
    if(start >= end) return;
    int pIndex = partition(edges , start , end);
    qS(edges , start , pIndex - 1);
    qS(edges , pIndex + 1 , end);
}

void quickSort(int** edges , int E) {
    qS(edges , 0 , E - 1);
}

int getUltimateParent(DSU* dsu, int x) {
    Node* node = dsu->nodes[x];

    Node* root = node;
    while (root->parent != root) {
        root = root->parent;
    }

    while (node->parent != node) {
        Node* nxt = node->parent;
        node->parent = root;
        node = nxt;
    }

    return root->index;
}

bool unite(DSU* dsu , int src , int dest) {
    int srcParent = getUltimateParent(dsu , src);
    int destParent = getUltimateParent(dsu , dest);

    if(srcParent == destParent) return false;

    if(dsu->nodes[srcParent]->rank == dsu->nodes[destParent]->rank) {
        dsu->nodes[destParent]->rank++;
        dsu->nodes[srcParent]->parent = dsu->nodes[destParent];
    }
    else if (dsu->nodes[srcParent]->rank > dsu->nodes[destParent]->rank) {
        dsu->nodes[destParent]->parent = dsu->nodes[srcParent];
    }
    else {
        dsu->nodes[srcParent]->parent = dsu->nodes[destParent];
    }

    return true;
}

int main() {
    int V,E;
    printf("Please enter the number of vertices and edges : ");
    scanf("%d%d" , &V , &E);

    int** edges = (int**)malloc(E*sizeof(int*));
    for(int i = 0 ; i<E ; i++) {
        edges[i] = (int*)malloc(3*sizeof(int));
    }

    printf("Please enter the edges below : \n");
    for(int i = 0 ; i<E ; i++) {
        printf("Edge %d: ", i + 1);
        scanf("%d%d%d" , &edges[i][0] , &edges[i][1] , &edges[i][2]);
    }

    DSU dsu;
    initDSU(&dsu , V);

    quickSort(edges , E);

    int cost = 0;
    printf("\nEdges in MST:\n");

    for(int i = 0 ; i<E ; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        if(unite(&dsu , u , v)) {
            cost += w;
            printf("%d -- %d  (weight %d)\n", u, v, w);
        }
    }

    printf("\nTotal cost of MST = %d\n", cost);
    return 0;
}
