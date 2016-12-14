/******************************************************************************/
/*****************************  prologue  *************************************/
/*                                                                            */
/*    University of California Extension, Santa Cruz                          */
/*                                                                            */
/*    Advanced C Programming                                                  */
/*                                                                            */
/*    Instructor: Rajainder A. Yeldandi                                       */
/*                                                                            */
/*    Author: Praveen Mhapsekar                                               */
/*                                                                            */
/*    Assignment Number: 13                                                   */
/*                                                                            */
/*    Topic: Binary Tree                                                      */
/*                                                                            */
/*    File name:  praveen-assignment-13.c                                     */
/*                                                                            */
/*    Date: 12/09/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*		Read the following numbers from an input file directly as integer     */
/*		values in to a binary tree.                                           */
/*		(Note: Do not assign an array with input values.).                    */
/*		55, 62, 89, 85, 97, 56, 71, 82, 38, 49, 25, 67, 58, 92, 100, 44, 69,  */
/*		72, 65, 52, 41, 84, 21, 60, 95, 12, 35, 42, 105, 99, 34, 47, 35, 79,  */
/*	   	95, 50, 25, 51                                                        */
/*                                                                            */
/*		Using a binary tree structure read the numbers and form an inordered  */
/*      tree. All nodes to the left subtree of the root will be lower than    */
/*      root and all nodes in the right subtree are higher.                   */
/*                                                                            */
/*		Traverse the tree in preorder, inorder, postorder, and print the      */
/*		data value (info) in the node when the node is visited.               */
/*		Write a delete algorithm to delete nodes and replacing them with      */
/*		their inorder successor.                                              */
/*                                                                            */
/*		Print the values inorder after all deletes.                           */
/*		Write both non-recursive and recursive routines to traverse the trees.*/
/*		User intends to find the following values in the tree.                */
/*		Verify and print message the whether the values are found in the tree */
/*		or not:                                                               */
/*		71, 51, 38, 5, 0, 25, 42, 91, 35 and 47                               */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "binaryTree.h"

#define FILE_IN  "praveen-assignment-13-input.doc"
#define FILE_OUT "praveen-assignment-13-output.doc"


void
dataProcessing()
{
	int  data;
	char choice = 'y';
    nodePtr tree = NULL;

	/* Open input & output files */
    finput = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT, "w");

	/* Read data from file and process it */
	fprintf(fout, "Reading data from input file and inserting data into the tree :\n");
    while (fscanf(finput, "%d", &data) == 1) {
		fprintf(fout, "Insert %d\n", data);
        insertTree(&tree, data);
    }

	/* preOrder traversal */
	fprintf(fout, "preOrder Traversal :\n");
	preorder(tree);
	fprintf(fout, "\n");

	/* inOrder traversal */
	fprintf(fout, "inOrder Traversal :\n");
	inorder(tree);
	fprintf(fout, "\n");

	/* postOrder traversal */
	fprintf(fout, "postOrder Traversal :\n");
	postorder(tree);
	fprintf(fout, "\n");

	/* Accept user input and delete items from the tree */
	while (choice == 'y') {
		__fpurge(stdin);
		printf ("Enter number to be deleted :\n");
		fprintf (fout, "Enter number to be deleted :\n");
		if (scanf("%d", &data) != 1) {
			printf("Invalid  number, please re-enter!!!\n"); 
			fprintf(fout, "%d", data);
			fprintf(fout, "Invalid  number, please re-enter!!!\n"); 
		} else {
			/* Print user entered item to out file*/
			fprintf(fout, "%d\n", data); 

			/* Delete item from the tree */
		 	if (!deleteTree(&tree, data)) {
                fprintf(fout, "%d, not found in the tree\n", data);
			} else {
				fprintf(fout, "inOrder Traversal after deletion of %d\n", data);
				inorder(tree);
				fprintf(fout, "\n");
			}

			/* Prompt user to continue */
			while (1) {
				__fpurge(stdin);
				printf ("Do you want to continue (y/n)?");
				if (scanf("%c", &choice) != 1) {
					printf("Invalid choice\n");
				} else {
					break;
				}
			}
		}
	}

	fprintf(fout, "\n");

	/* close files */
    fclose(finput);
	fclose(fout);
}

int
main(void) 
{
    dataProcessing();
    return 0;
}
