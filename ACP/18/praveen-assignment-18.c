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
/*    Assignment Number: 18                                                   */
/*                                                                            */
/*    Topic: LinkedList                                                       */
/*                                                                            */
/*    File name:  praveen-assignment-18.c                                     */
/*                                                                            */
/*    Date: 12/19/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*		Read the following two long integer inputs from an input file in      */
/*		the same order.                                                       */
/*		List 1:                                                               */
/*		954680325257568512973371196238845129776544789456                      */
/*		List 2:                                                               */
/*		64324564257936835497210698463523456234                                */
/*		Using a list structure read the numbers and forms a linear linked list*/
/*		print the list elements as list1 and list2. Consider reading 4 or 5   */
/*		digits  at a time into the node.                                      */
/*      Write an addition algorithm to process the two long integer list      */
/*		structures into a result list.                                        */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include "linkedList.h"

#define FILE_IN_1 "praveen-assignment-18-input-1.doc"
#define FILE_IN_2 "praveen-assignment-18-input-2.doc"
#define FILE_OUT  "praveen-assignment-18-output.doc"

/* 
   This function will,
   - Read long integers from the files.
   - Add leading zeros to the number if needed.
   - Print both intergers in human readble form.
   - Add both integers and save sum.
   - Print sum of two long integers.
*/

void
inputFileProcessing()
{
    FILE *finput1; /* Input file pointer */
    FILE *finput2; /* Input file pointer */
	FILE *fout;    /* Output file pointer */
	char  data;
	int   carry;
	char  cnt1 = 0;
	char  cnt2 = 0;
    node_t *list1 = NULL; /* List pointers */
    node_t *list2 = NULL;
    node_t *list3 = NULL;

	/* Open input & output files */
    finput1 = fopen(FILE_IN_1, "r");
    finput2 = fopen(FILE_IN_2, "r");
    fout = fopen(FILE_OUT, "w");

	/* Read data from first file and add to the list */
    while ((data = fgetc(finput1)) != EOF) {
		data -= '0';
		if ((data >= 0) && (data <= 9)) {
			insertList(&list1, data);
			cnt1++;
		}
    }

	/* Read data from second file and add to the list */
    while ((data = fgetc(finput2)) != EOF) {
		data -= '0';
		if ((data >= 0) && (data <= 9)) {
			insertList(&list2, data);
			cnt2++;
		}
    }

	/* Adjust/Add leading zero*/
    reverseList(&list1);
    reverseList(&list2);

	if (cnt1 > cnt2) {
        while (cnt1 != cnt2) {
		    insertList(&list2, 0);
		    cnt2++;
	    }
    } else {
        while (cnt2 != cnt1) {
		    insertList(&list1, 0);
		    cnt1++;
	    }
	}

	/* Print both lists to be added */
    fprintf(fout, "1st long integer:\t");
	printList(fout, list1);
    fprintf(fout, "2nd long integer:\t");
	printList(fout, list2);


	/* Add both intergers digit by digit & store sum in list3 */
    reverseList(&list1);
    reverseList(&list2);
	carry = 0;
	while (list1 && list2) {
        data = list1->data + list2->data + carry;
		carry = data / 10;
		data  = data % 10;
		insertList(&list3, data);
		list1 = list1->nxt;
		list2 = list2->nxt;
	}

#if 0 
	 /* This code is not needed, 
		 leading zero processing will take care of it
		 Both lists are of same size.
	  */
	if (!list1) {
        while(list2) {
			insertList(&list3, list2->data);
			list2 = list2->nxt;
		}
	}

	if (!list2) {
        while(list1) {
			insertList(&list3, list1->data);
			list1 = list1->nxt;
		}
	}
#endif

	/* Print sum (list3) */
    fprintf(fout, "%*c", 20, ' ');
	while(cnt2) {
         fprintf(fout, "%c", '-');
		 cnt2--;
	}
    fprintf(fout, "\nsum of two int:\t\t");
    printList(fout, list3);	
	fprintf(fout, "\n");

	/* Close files */
    fclose(finput1);
    fclose(finput2);
	fclose(fout);
}

int
main(void) 
{
    inputFileProcessing();
    return 0;
}
