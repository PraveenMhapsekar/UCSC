#include "binaryTree.h"

/* Tree Insert recursive function */
void
insertTree(nodePtr *tree, int n) 
{
    nodePtr temp;

    if (*tree == NULL) {
	   temp = (nodePtr)malloc(sizeof(node_t));
	   temp->data = n;
	   temp->left = NULL;
	   temp->right = NULL;
       *tree = temp;
    } 

	if (n < (*tree)->data) {
		insertTree(&(*tree)->left, n);
    }
   
	if (n > (*tree)->data) {
		insertTree(&(*tree)->right, n);
	}
}

/* Delete node from tree */
bool
deleteTree(nodePtr *root, int n)
{
    nodePtr temp;
    bool ret = true;

    if (*root == NULL) {
		return false;
	}

    if (n < (*root)->data) {
        ret = deleteTree(&((*root)->left), n);
    } else if (n > (*root)->data) {
        ret = deleteTree((&(*root)->right), n);
    } else {
        if ((*root)->left && (*root)->right) {
            temp = findMaxTree((*root)->left);
            (*root)->data = temp->data;
            ret = deleteTree((&(*root)->left), (*root)->data);
        } else {
            temp = *root;

            if ((*root)->left)
                *root = (*root)->left;
            else if ((*root)->right)
                *root = (*root)->right;
            else 
                *root = NULL;

            free(temp);
        }
    }

	return ret;
}

/* Find max node of the given tree */
nodePtr
findMinTree (nodePtr root) 
{
   while (root->left)
       root = root->left;

   return(root);   
}

/* Find min node of the given tree */
nodePtr
findMaxTree (nodePtr root) 
{
   while (root->right)
       root = root->right;

   return(root);
}

/* Inorder traversal */
void 
inorder(nodePtr tree) 
{
   if (NULL == tree) 
       return;        // Base case

   if (tree->left)
       inorder(tree->left);    // Visit left subtree

   fprintf(fout, "%3d ", tree->data);  // Visit node

   if (tree->right)
       inorder(tree->right);    // Visit right subtree

   return; 
}

/* postorder traversal */
void 
postorder(nodePtr tree) 
{
    if (NULL == tree) 
        return; //basecase

    if (tree->right)
        postorder(tree->right);   // Visit right subtree

    if(tree->left) 
        postorder(tree->left);   // Visit left subtree

    fprintf(fout, "%3d ", tree->data);   // Visit node
}

/* preorder traversal */
void
preorder(nodePtr tree) 
{
    if (NULL == tree)
       return;  //basecase

    fprintf(fout, "%3d ", tree->data);   // Visit node

    if (tree->left)  
        postorder(tree->left);    // Visit left subtree

    if (tree->right)
        postorder(tree->right);   // Visit right subtree
}

#if 0
void inorder_iterative(BinaryTree *root) {
  stack<BinaryTree*> s;
  s.push(root);
  while (!s.empty()) {
    BinaryTree *top = s.top();
    if (top != NULL) {
      if (!top->visited) {
        s.push(top->left);
      } else {
        cout << top->data << " ";
        s.pop();
        s.push(top->right);
      }
    } else {
      s.pop();
      if (!s.empty())
        s.top()->visited = true;
    }
  }
}
#endif

/* Least Common Ancester */
nodePtr
LCA (nodePtr tree, nodePtr A, nodePtr B) 
{
    if (!tree)
        return NULL;
    if ((tree->left) && (tree->right))
        return tree;
    if ((tree == A) || (tree == B))
        return tree;
    if (tree->left)
        LCA(tree->left, A, B);
    if (tree->right)
        LCA(tree->right, A, B);        
}

void
kthSmallest(nodePtr tree, int *count, nodePtr *ret) 
{

    if (!tree) 
        return;

    if (tree->left) 
        kthSmallest(tree->left, count, ret);

    if ((*count) == 0) {
        *ret = tree;
    }
    (*count)--;
    if (tree->right) 
       kthSmallest(tree->right, count, ret);
}

#ifdef TREE_TEST
/* Driver program to test tree functionality */
int main() 
{
    nodePtr tree = NULL;

    nodePtr tree1 = NULL;
    nodePtr node, node1, lcm;
    int count = 0;
    int n;

    insertTree(&tree, 10);
    insertTree(&tree, 20);
    insertTree(&tree, 15);
    insertTree(&tree, 13);
    insertTree(&tree, 3);
    insertTree(&tree, 5);
    insertTree(&tree, 17);
    insertTree(&tree, 113);

    node = findMaxTree(tree);
    fprintf(fout, "Max number %d\n", node->data);

    node1 = findMinTree(tree);
    fprintf(fout, "Min number %d\n", node1->data);

    fprintf(fout, "inorder\n");
    inorder(tree);
    fprintf(fout, "\n");

    lcm = LCA(tree, node, node1);
    fprintf(fout, "LCA of %d and %d is %d\n", node->data, node1->data, lcm->data);
    n = 20;
    fprintf(fout, "Delete %d from tree\n", n);
    deleteTree(&tree, n);

    fprintf(fout, "Postorder\n");
    postorder(tree);
    fprintf(fout, "\n");

    fprintf(fout, "Preorder\n");
    preorder(tree);
    fprintf(fout, "\n");

    fprintf(fout, "inorder\n");
    inorder(tree);
    fprintf(fout, "\n");

    for (n = 0; n < 8; n++) {
        count = n;
        node = NULL;
        kthSmallest(tree, &count, &node);
        if (node)
            fprintf(fout, "kth(%d) smallest number is %3d\n", n, node->data); 
    } 
    return 0;
}
#endif
