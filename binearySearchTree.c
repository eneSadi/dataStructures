#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node *left, *right;
};

void printInorder(struct node* root){

    if(root == NULL){
        return;
    }
    printInorder(root->left);
    printf("%d -- ",root->value);
    printInorder(root->right);
}

struct node* createNode(int value){
    struct node *tmp;
    tmp = (struct node*)malloc(sizeof(struct node));
    if(tmp == NULL){
        exit(0);
    }
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->value = value;
    return tmp;
}

struct node* insert(struct node* root, int value){

    if(root == NULL){
        return createNode(value);
    }
    else{
        printf("\nvalue => %d , root->value => %d, root => %p , root->left => %p , root->right => %p\n",value, root->value, root, root->left, root->right);
        if(root->value > value){
            root->left = insert(root->left, value);
        }
        else{
            root->right = insert(root->right, value);
        }
        
        return root;
    }
}

struct node* search(struct node *root, int value){
    
    struct node *tmp = root;

    while((tmp) && (tmp->value != value)){
        if(value < tmp->value){
            tmp = tmp->left;
        }
        else{
            tmp = tmp->right;
        }
    } 
    return tmp;
}

struct node* findInorderSuccessor(struct node *tmp){

    
    while(tmp){

        tmp = tmp->left;
    }
    return tmp;

}

struct node* delete(struct node *root, int value){

    struct node *tmp = root;
    struct node *upperNode = root;
    int leftOrRight;

    while((tmp) && (tmp->value != value)){
        if(value < tmp->value){
            upperNode = tmp;
            leftOrRight = 1;
            tmp = tmp->left;
        }
        else{
            upperNode = tmp;
            leftOrRight = 0;
            tmp = tmp->right;
        }
    }

    if(tmp == NULL){
        return root;
    }
    else if(tmp->right == NULL && tmp->left == NULL){
        if(leftOrRight){
            upperNode->left = NULL;
        }
        else{
            upperNode->right = NULL;
        }
        free(tmp);
        return root;
    }

    else if(tmp->left == NULL && tmp->right != NULL){
    
        if(leftOrRight){
            upperNode->left = tmp->right;
        }
        else{
            upperNode->right = tmp->right;
        }
        free(tmp);
        return root;
    }
    else if(tmp->right == NULL && tmp->left != NULL){

        if(leftOrRight){
            upperNode->left = tmp->left;
        }
        else{
            upperNode->right = tmp->left;
        }
        free(tmp);
        return root;
    }
    else{
        struct node *inorderSuccessor = tmp->right;
        struct node *ancestor = tmp->right;

        while(inorderSuccessor->left){
            ancestor = inorderSuccessor;    
            inorderSuccessor = inorderSuccessor->left;
        }
        
        tmp->value = inorderSuccessor->value;
        ancestor->left = NULL;
        if(inorderSuccessor->right != NULL){
            tmp->right = inorderSuccessor->right;
        }
        free(inorderSuccessor);
        return root;
    }
}

int main(){

    struct node *root = NULL;

    root = insert(root, 100);
    root = insert(root, 90);
    root = insert(root, 150);
    root = insert(root, 80);
    root = insert(root, 145);
    root = insert(root, 160);
    root = insert(root, 170);
    root = insert(root, 148);
    root = insert(root, 130);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 165);


    printInorder(root);
    printf("\n\n");
    
    root = delete(root, 80);
    printInorder(root);
    printf("\n\n");
    
    root = delete(root, 130);
    printInorder(root);
    printf("\n\n");
    
    root = delete(root, 150);
    printInorder(root);
    printf("\n\n");

    return 0;
}