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
/*    Assignment Number: 17                                                   */
/*                                                                            */
/*    Topic: Infix to Prefix conversion                                       */
/*                                                                            */
/*    File name:  praveen-assignment-17.c                                     */
/*                                                                            */
/*    Date: 12/20/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*        Use the functions PUSH, POP, INFIX, PREFIX_Convert, PREFIX_Eval     */
/*		  and other required.                                                 */
/*        Read the input into a buffer from input file.                       */
/*        Place a space between numbers and operators, numbers and numbers,   */
/*        and operators and operators. (Note: Do not initialize an array with */
/*        input values.). Convert the following expression from infix notation*/ 
/*        to prefix notation.                                                 */
/*    Expression:                                                             */
/*	(25 % 7 * 8) / (75 / 5 – 8 + (2 ^ 4 – (2 ^ 2 + 16) + 16 – 3) + 5 – 3 ^ 2) */
/*        Using an array structure read the numbers from an input file.       */
/*	      Print the original infix notation                                   */
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
