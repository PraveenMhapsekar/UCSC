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
/*    Assignment Number: 09                                                   */
/*                                                                            */
/*    Topic: Queue                                                            */
/*                                                                            */
/*    File name:  praveen-assignment-09.c                                     */
/*                                                                            */
/*    Date: 11/18/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/* 	    Implement a queue data structure using an array. Read the             */
/*		choice and data input from a file. Perform Enque or                   */
/*		Deque operations depending on the choice of the input                 */
/*		preceding the data element. Print what is being inserted              */
/*		and what data is removed from the queue. When the                     */
/*		choice is to perform Enque, you will read the choice and              */
/*		data. But when the choice is to perform Deque, there is               */
/*		no data to be read.                                                   */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include "queue.h"

#define FILE_IN  "praveen-assignment-09-input.doc"
#define FILE_OUT "praveen-assignment-09-output.doc"

#define QSIZE 64

void
inputFileProcessing()
{
    FILE *finput; /* Input file pointer */
	FILE *fout;   /* Output file pointer */
    char token;
	int data;
    queue_t *Q;

	/* Create queue */
    Q = createQ(QSIZE);

	/* Open input & output files */
    finput = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT, "w");

	/* Read token from file and process it */
    while ((token = fgetc(finput)) != EOF) {
        switch (token) {
            case 'E' :
				fscanf(finput, "%d", &data);
				fprintf(fout, "Enque %d\n", data);
				/* Enque data */
				enQueue(Q, data); 
				break;
            case 'D' :
				/* Deque data */
				data = deQueue(Q); 
				fprintf(fout, "Deque %d\n", data);
				break;
            default:
                break;
        }
        fflush(stdout);
    }

	/* close files */
    fclose(finput);
	fclose(fout);
}

int
main(void) 
{
    inputFileProcessing();
    return 0;
}
