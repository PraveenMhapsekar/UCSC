#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__

typedef struct node {
    int data;
    struct node *nxt;
} node_t;

void insertList(node_t **head, int data);
int  deleteList(node_t **Head, int data);
void printList(FILE *fileptr, node_t *head);
void reverseList(node_t **head); 

#endif	
