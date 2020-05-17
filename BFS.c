#include<stdio.h>
#include<stdlib.h>

//GRAPH FUNCTIONS
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

//QUEUE FUNCTIONS
struct QNode{
    int value;
    struct QNode *next;
};

struct Queue{
    struct QNode *front, *rare; 
};

struct Queue *createQueue(){

    struct Queue *q;
    q = (struct Queue*)malloc(sizeof(struct Queue));
    if(q == NULL){
        exit(0);
    }
    else{
        q->front = q->rare = NULL;
        return q;
    }
}

void enqueue(struct Queue *q, int value){

    struct QNode *tmp;
    tmp = (struct QNode*)malloc(sizeof(struct QNode));
    if(tmp == NULL){
        exit(0);
    }
    tmp->value = value;
    tmp->next = NULL;
    if(q->front == NULL){
        q->front = q->rare = tmp;
    }
    else{
        q->rare->next = tmp;
        q->rare = tmp;
    }
}

int dequeue(struct Queue *q){

    int value;
    if(q->front == NULL){
        printf("Queue is empty!\n");
        return -1;
    }
    else{
        value = q->front->value;
        struct QNode *tmp;
        tmp = q->front;
        q->front = tmp->next;
        
        if(q->front == NULL){
            q->rare = NULL;
        }
        free(tmp);
        
        return value;
    }
}

void printQueue(struct QNode *q){

    struct QNode *tmp = q;
    while(tmp->next){
        printf("%d --- ",tmp->value);
        tmp = tmp->next;
    }
    printf("%d\n\n",tmp->value);
}

void BFS(struct Graph *myGraph, int s){
    struct Graph *G = myGraph;

    int *visited = (int*)malloc(G->numVertices * sizeof(int));
    int v, i;
    for(i = 0 ; i < G->numVertices ; i++){
        visited[i] = -1;
    }

    struct Queue *queue = createQueue();
    enqueue(queue, s);
    visited[s] = 0;
    printf("\n%d --", s);

    while(queue->front != NULL){
        v = dequeue(queue);
        
        struct node *tmp = G->adjLists[v];
        while(tmp){
            if(visited[tmp->vertex] == -1){

                enqueue(queue, tmp->vertex);
                visited[tmp->vertex] = visited[v] + 1;
                printf(" %d --", tmp->vertex);
            }
            tmp = tmp->next;
        }
    }
}

int main(){

    struct Graph *G = createGraph(5);
    addEdge(G, 0, 3);
    addEdge(G, 0, 1);
    addEdge(G, 3, 4);
    addEdge(G, 2, 3);
    
    BFS(G, 0);
    printf("\n\n");
    printGraph(G);

    return 0;
}

