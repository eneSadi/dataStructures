#include<stdio.h>
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



int main(){

    STACK *s;
    s->top = 0;

    



    return 0;
}