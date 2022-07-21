/**
  ******************************************************************************
  * @file    main.c
  * @author  Andres Estrada
  * @brief   Main program body: This program open and read a file of integers,save these values 
  *          into an integer array of size from the first value. Then, these values are placed 
  *          into a binary tree structure. Finally is traversed and printed the tree inorder.
  ******************************************************************************
**/
#include <stdio.h>
#include <stdlib.h>
#define MAX_NUMS 20

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
}node;

node* init_node(int d, node* p1, node* p2){
    // Allocate memory for new node
    node* node = malloc(sizeof(struct node));
    node->data = d;
    node->left = p1;
    node->right = p2;
    return node;
}

node* create_node(int a[], int i, int size){
    //If completed return null pointer
    if (i >= size)
        return NULL;
    else
        //Initialize node: create right pointer and left
        //Multiply each pointer by 2 since the tree bifurcates by that factor
        return (init_node(a[i],
                create_node(a, 2*i + 1, size),
                create_node(a, 2*i + 2, size)));
}

void inorder(node* root){
    if(root != NULL){
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void read_data(FILE *ptr, int d[], int *size){
    //Read first element, save it in size
    fscanf(ptr, "%d", &(*size));
    //Loop for read the elements
    for(int i=0; i<(*size); i++){
        //Save each number in the array
        fscanf(ptr, "%d", &d[i]);
    }
}

int main(void){
    //Pointer for storing information from the file
    FILE *ifp;
    node* tree;
    int sz, data[MAX_NUMS];

    //Open Stream
    ifp = fopen("nums.txt", "r");
    //Read data from file and save the size value and its elements into data[]
    read_data(ifp, data, &sz);

    //Create tree structure 
    tree = create_node(data, 0, sz);
    //Print tree in inorder traverse
    printf("Inorder: \n");
    inorder(tree);
    
    printf("\n\n");
    //Close stream
    fclose(ifp);
    return 0;
}
