#ifndef __BINARY_TREE_H__
#define  __BINARY_TREE_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *finput; /* Input file pointer */
FILE *fout;   /* Output file pointer */

typedef struct node *nodePtr;

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;

void
insertTree(nodePtr *tree, int n);

bool
deleteTree(nodePtr *root, int n);

nodePtr 
findMinTree (nodePtr root);

nodePtr 
findMaxTree (nodePtr root);

void
preorder(nodePtr tree);

void
inorder(nodePtr tree);

void
postorder(nodePtr tree);
#endif
