/**
  ******************************************************************************
  * @file    main.c
  * @author  Andres Estrada
  * @brief   Main program body: This program generate random integers [0,49], save 
  *          those on a doubly linked list of  size 200. Then, the list  is sorted
  *          and finally remove the repeated elements.
  ******************************************************************************
**/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define size 200

typedef struct list{
    int data;
    struct list *prev;
    struct list *next;
}list;

int isempty(list *h){
    return (h == NULL);
}

void addfront(list** h, int d){
    //create node
    list* head = malloc(sizeof(list));
    head->data = d;
    head->next = (*h);
    head->prev = NULL;

    if (!isempty(*h))
        (*h)->prev = head;
    
    (*h) = head;
}

void bubbleSort(list *h) {
    list *h0;
    list *h1 = NULL;
    for (int step = 0; step < size - 1; ++step) {
        h0 = h;
        int swapped = 0;
        for (int i = 0; i < size - step - 1; ++i) {
            if (h0->data > h0->next->data) {
                int temp = h0->data;
                h0->data = h0->next->data;
                h0->next->data = temp;
        
                swapped = 1;
            }
            h0 = h0->next;
        }
    
        if (swapped == 0) {
            break;
        }
        h1 = h0;
    }
    free(h0);
    free(h1);
}

int delDuplicates(list* h, int size_n){
    list *h0 = h;
    int rn_size = size_n;
    for (int i = 0; i < size_n; ++i) {
        if(h0->next != NULL)
            h0 = h0->next;
        if (h0 != NULL && h0->prev != NULL && h0->prev->data == h0->data){
            h0->prev->next = h0->next;
            if(h0->next != NULL)
                h0->next->prev = h0->prev;
            else{
                h0->prev = h0->prev->prev;
            }
            rn_size -= 1;
        }
    }
    free(h0);
    return rn_size;
}

void printlist(list *h, int size_n){
    list* last;
    printf("\nTraversal in forward direction \n");
    while (h != NULL){
        for (int i = 0; i < size_n; i++){
            printf("%d ", h->data);
            last = h;
            h = h->next;
        }
        printf("\n");
    }
    printf("\nTraversal in reverse direction \n");
    while (last != NULL) {
        for (int i = 0; i < size_n; i++){
            printf("%d ", last->data);
            last = last->prev;
        }
        printf("\n");
    }
    free(last);
}

int main(void){
    srand(time(0));
    list* head = NULL;

    for (int i = 0; i < size; i++){
        addfront(&head, rand() % 50);
    }
    
    printlist(head, size);
    bubbleSort(head);
    printf("\n\nOrdered List\n");
    printlist(head, size);

    printf("\n\nList without repeated\n");
    int n_size = delDuplicates(head, size);
    printlist(head, n_size);
     return 0;
}
