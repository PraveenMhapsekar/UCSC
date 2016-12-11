#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void
insertList(node_t **head, int data) 
{
    node_t *tmp;

    tmp = (node_t *)malloc(sizeof(node_t));
    if (NULL == tmp) {
        printf("malloc failed\n");
    }

    tmp->data = data; 
    tmp->nxt  = *head;

    *head = tmp;
    return;
}

int 
deleteList(node_t **Head, int data) 
{
    node_t *tHead;
    node_t *tmp;

    if (*Head == NULL) {
        printf("Empty List \n");
    }

    while (*Head && (*Head)->data == data) {
        tmp = *Head;
        *Head = (*Head)->nxt;
        free(tmp);
    }

    tHead = *Head;

    while (tHead && tHead->nxt) {
        if (tHead->nxt->data == data) {
           tmp = tHead->nxt;
           tHead->nxt = tHead->nxt->nxt;
           free(tmp);
        } else {
           tHead = tHead->nxt;
        }
    }

    return 0;
}

void
printList(FILE *filePtr, node_t *head) 
{
    if (!head) {
        fprintf(filePtr, "Empty List\n");
    }

    while(head) {
        fprintf(filePtr, "%d ", head->data);
        head = head->nxt;
    }
    fprintf(filePtr, "\n");
    return;
}

void
reverseList(node_t **head) 
{
    node_t *cur = NULL;
    node_t *pre = NULL;
    node_t *nxt = NULL;

    if (*head == NULL) 
        return;    

    cur = *head;    // head of the list
    nxt = cur->nxt; // head next

    while(nxt) {
        cur->nxt = pre;  // connect cur to previous
        pre = cur;       // now, cur becomes previous for next iteration
        cur = nxt;       // keep moving cur and nxt pointers on origional list
        nxt = nxt->nxt;  // keep moving cur and nxt pointers on origional list
    }

    cur->nxt = pre; // connect last cur node to pre
    *head = cur;    // return cur (last node)
    return;
}

#ifdef TEST_LINKED_LIST
int main() 
{
    node_t *list = NULL;
    insert(&list, 1);
    insert(&list, 2);
    insert(&list, 3);
    insert(&list, 4);
    insert(&list, 5);
    insert(&list, 6);
    insert(&list, 7);
    insert(&list, 8);
    print(list);

    reverse(&list);
    print(list);

    myreverse(&list);
    print(list);
#if 0

    insert(&list, 5);
    insert(&list, 5);
    insert(&list, 5);
    insert(&list, 5);
    insert(&list, 5);
    print(list);
#endif
#if 0
   // reverse(&list);
   // print(list);
    //oddeven(list);
    delete(&list, 5);
  //  print(list);

   // delete(&list, 1);
    print(list);
    reverse(&list);
    print(list);
    oddeven(list);

    reversepair(&list);
    print(list);
    delete(&list, 4);
    print(list);
    delete(&list, 2);
    print(list);
    delete(&list, 3);
    print(list);

    print(list);
#endif
    return 0;
}
#endif
