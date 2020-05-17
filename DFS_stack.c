//printGraph ve DFS aynı anda çalışınca pointer kaybından biri yanlış çalışıyor yedek tutulması gerek.

#include<stdio.h>
#include<stdlib.h>
#define MAX 100

typedef struct{
    int item[MAX];
    int top;
}STACK;

int isEmpty(STACK *s){
    if(s->top == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int isFull(STACK *s){
    if(s->top == MAX){
        return 1;
    }
    else{
        return 0;
    }
}

int push(STACK *s, int x){

    if(isFull(s)){
        return 0;
    }
    else{
        s->item[(s->top)++] = x;
        return 1;
    }
}

int pop(STACK *s, int *x){

    if(isEmpty(s)){
        return 0;
    }
    else{
        *x = s->item[--(s->top)];
        return 1;
    }
}

int peek(STACK *s, int *x){

    if(isEmpty(s)){
        return 0;
    }
    else{
        *x = s->item[(s->top)-1];
        return 1;
    }
}

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

void DFS(struct Graph *G, int s){

    STACK *stack = (STACK*)malloc(sizeof(STACK));
    stack->top = 0;
    int *visited = (int*)calloc(G->numVertices, sizeof(int));
    
    int v, j;
    push(stack, s);
    visited[s] = 1;
    printf("\n%d --", s);

    while(!isEmpty(stack)){

        pop(stack, &v);
        while(G->adjLists[v]){
            if(!visited[G->adjLists[v]->vertex]){
                push(stack, G->adjLists[v]->vertex);
                visited[G->adjLists[v]->vertex] = 1;
                printf(" %d --", G->adjLists[v]->vertex);
            }
            G->adjLists[v] = G->adjLists[v]->next;
        }

    }

}

int main(){

    struct Graph *G = createGraph(5);
    addEdge(G, 0, 3);
    addEdge(G, 0, 1);
    addEdge(G, 3, 4);
    addEdge(G, 2, 3);
    //printGraph(G);

    DFS(G, 0);
    printf("\n\n");
    


    return 0;
}
