#include<stdio.h>
#include<stdlib.h>

struct node{
    int vertex;
    struct node *next;
};

struct Graph{
    int numVertices;
    struct node **adjLists;
};

struct node* createNode(int vertex){

    struct node *newNode = malloc(sizeof(struct node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices){

    int i;
    struct Graph *graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    for(i = 0 ; i < vertices ; i++){
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(struct Graph* graph, int src, int dest){
    
    struct node *newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void printGraph(struct Graph *g){

    for(int i = 0 ; i < g->numVertices ; i++){
        printf("%d -->", i);
        while(g->adjLists[i]){
            printf("%d ", g->adjLists[i]->vertex);
            g->adjLists[i] = g->adjLists[i]->next;
        }
        printf("\n");
    }
}

int main(){

    struct Graph *myGraph = createGraph(10);

    addEdge(myGraph, 3, 4);
    addEdge(myGraph, 0, 2);

    printGraph(myGraph);


    

    return 0;
}