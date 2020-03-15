#include<stdio.h>
#include<stdlib.h>

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

void yazdir(struct QNode *q){

    struct QNode *tmp = q;
    while(tmp->next){
        printf("%d --- ",tmp->value);
        tmp = tmp->next;
    }
    printf("%d\n\n",tmp->value);
}


int main(){

    struct Queue *q;
    int value;
    q = createQueue();

    enqueue(q,10);
    enqueue(q,20);
    enqueue(q,30);
    enqueue(q,40);
    enqueue(q,50);
    yazdir(q->front);

    value = dequeue(q);
    printf("%d ile isi bitti...\n",value);
    yazdir(q->front);

    return 0;
}