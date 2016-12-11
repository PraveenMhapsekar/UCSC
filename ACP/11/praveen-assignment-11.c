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
/*    Assignment Number: 11                                                   */
/*                                                                            */
/*    Topic: LinkedList                                                       */
/*                                                                            */
/*    File name:  praveen-assignment-11.c                                     */
/*                                                                            */
/*    Date: 12/09/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*		Read the following numbers from input file as integers in the         */
/*		same order.                                                           */ 
/*		49, 17, 56, 85, 12, 97, 33, 71, 19, 62, 38, 84, 51,                   */
/*		29, 77, 65, 44, 99, 4, 47, 67, 41, 23, 88, 73, 8, 10,                 */
/*		100, 25, 91, 58, 45, 22, 15, 35, 95, 60, 20, 7, 50                    */
/*                                                                            */
/*		Form a linked list with the input numbers from a file.                */
/*		Using a list structure read the numbers and form a linear linked list,*/
/*		print the list elements after populating in the original order.       */
/*		Reverse the original linked list and print the reversed list.         */
/*		Prompt the user to enter an integer to be deleted from the nodes and  */
/*		maintain the list. Do not use the buffer or another input file to     */
/*		contain the numbers to be deleted.                                    */
/*                                                                            */
/*		Quit removing elements when user intends to do so. Print prompting    */
/*		the user and the input receiving along with the result.               */
/*		                                                                      */
/*		User intends to delete the following valid and                        */
/*		invalid numbers one at time:                                          */
/*		71, 51, 38, 5, 0, 25, 42, 32 and 47                                   */
/*		print the list after removing elements.                               */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include "linkedList.h"

#define FILE_IN  "praveen-assignment-11-input.doc"
#define FILE_OUT "praveen-assignment-11-output.doc"

/* 
   This function will,
   Read data from input file and insert it into linked list
   - Reverse and Print linkedlist
   - Prompt user to enter items to be deleted and delete those items
*/

void
dataProcessing()
{
    FILE *finput; /* Input file pointer */
	FILE *fout;   /* Output file pointer */
	int  data;
	char choice = 'y';
    node_t *list = NULL;

	/* Open input & output files */
    finput = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT, "w");

	/* Read data from file and process it */
    while (fscanf(finput, "%d", &data) == 1) {
		fprintf(fout, "Insert %d\n", data);
        insertList(&list, data);
		printList(fout, list);
    }

	/* Reverse and print list */
    reverseList(&list);
    fprintf(fout, "reversed list:\n");
    printList(fout, list);	

	/* Accept user input and delete items from the list */
	while (choice == 'y') {
		__fpurge(stdin);
		printf ("Enter number to be deleted :");
		if (scanf("%d", &data) != 1) {
			printf("Invalid  number, please re-enter!!!\n"); 
		} else {
			/* Print user entered item */
			fprintf(fout, "Entered number to be deleted is %d\n", data); 
			/* Delete item form the list */
			deleteList(&list, data);
			/* Print list after deletion */
			printList(fout, list);
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
