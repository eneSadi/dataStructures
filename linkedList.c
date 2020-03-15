#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node *next;
};

void insertSorted(struct node* head){

    struct node *current = head;
    
    int value;
    printf("What is the value of node: ");
    scanf("%d",&value);

    struct node *node = (struct node*)malloc(sizeof(struct node));
    node->value = value;
        
    if(value < current->value){     
        node->next = current;
        head = node;
    }
    else{
        struct node *prev = head;
        while(current->next && value > current->value){
            prev = current;
            current = current->next;
        }
        node->next = current;
        prev->next = node;
    }

}

void list(struct node *head){

    struct node *current = head;
    while(current->next){
        printf("%d\n",current->value);
        current = current->next;
    }
    printf("%d\n",current->value);
}


int main(){

    struct node *head = (struct node*)malloc(sizeof(struct node));
    head->next = NULL;
    printf("What is the first value: ");
    scanf("%d",&(head->value));

    char choice;
    printf("Sorted insertion process is beginning...\n--->'a' for add a new node\n--->'d' for delete a node\n--->'l' for list\n--->'q' for quit\n--------------------------------------------------\n");
    do{
        printf("Make your choice: ");
        scanf(" %c",&choice);
        if(choice == 'a'){
            insertSorted(head);
        }
        else if(choice == 'd'){
            //deleteNode(head);
        }
        else if(choice == 'l'){
            list(head);
        }

    }while(choice != 'q');

    return 0;
}