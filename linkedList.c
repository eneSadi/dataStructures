#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node *next;
};

struct node* insertSorted(struct node* head){

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
        if(value > current->value){
            current->next = node;
            node->next = NULL;
        }
        else{
            prev->next = node;
            node->next = current;
        }
    }
    return head;
}

void list(struct node *head){

    struct node *current = head;
    while(current->next){
        printf("%d\n",current->value);
        current = current->next;
    }
    printf("%d\n",current->value);
}

struct node* deleteNode(struct node *head){

    int value;
    printf("Which number you want to delete: ");
    scanf("%d",&value);

    struct node *current = head;
    struct node *before = head;

    while(current && current->value != value){
        before = current;
        current = current->next;
    }
    if(current == NULL){
        printf("This number is not there!\n");
    }
    else{
        if(current == head){
            head = current->next;
            printf("%d deleted successfully!\n", current->value);
            free(current);
        }
        else{
            before->next = current->next;
            printf("%d deleted successfully!\n", current->value);
            free(current);
        }
    }
    return head;
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
            head = insertSorted(head);
        }
        else if(choice == 'd'){
            head = deleteNode(head);
        }
        else if(choice == 'l'){
            list(head);
        }

    }while(choice != 'q');

    return 0;
}