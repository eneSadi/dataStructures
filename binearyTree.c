#include<stdio.h>
#include<stdlib.h>

struct node{
    int value;
    struct node *left, *right;
};

void printPreorder(struct node* root){

    if(root == NULL){
        return;
    }
    printf("%d -- ",root->value);
    printPreorder(root->left);
    printPreorder(root->right);
}
void printPostorder(struct node* root){

    if(root == NULL){
        return;
    }
    printPostorder(root->left);
    printPostorder(root->right);
    printf("%d -- ",root->value);
}
void printInorder(struct node* root){

    if(root == NULL){
        return;
    }
    printInorder(root->left);
    printf("%d -- ",root->value);
    printInorder(root->right);
}


int main(){

    struct node *root;
    
    root = (struct node*)malloc(sizeof(struct node));
    root->value = 3;
    root->left = (struct node*)malloc(sizeof(struct node));
    root->left->value = 5;
    root->right = (struct node*)malloc(sizeof(struct node));
    root->right->value = 8;
    root->left->left = (struct node*)malloc(sizeof(struct node));
    root->left->left->value = 9;
    root->left->right = (struct node*)malloc(sizeof(struct node));
    root->left->right->value = 7;
    root->right->right = (struct node*)malloc(sizeof(struct node));
    root->right->right->value = 1;
    root->right->right->right = (struct node*)malloc(sizeof(struct node));
    root->right->right->right->value = 6;

    printf("\n\n");
    printPreorder(root);
    printf("\n\n");
    printInorder(root);
    printf("\n\n");
    printPostorder(root);
    printf("\n\n");
    

    return 0;
}