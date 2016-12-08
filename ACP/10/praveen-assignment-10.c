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
/*    Assignment Number: 10                                                   */
/*                                                                            */
/*    Topic: Recursion                                                        */
/*                                                                            */
/*    File name:  praveen-assignment-10.c                                     */
/*                                                                            */
/*    Date: 12/08/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*      Implement Tower of Hanoi problem                                      */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>

#define FILE_OUT "praveen-assignment-10-output.doc"

#define N 5

FILE *fout;   /* Output file pointer */

void
move(char from, char to, int n)
{

   fprintf(fout, "moving %d from %c to %c\n", n, from, to);
}

void
towerOfHanoi(int n, char src, char dst, char aux)
{
	if (n == 1) {
		move(src, dst, n);
		return;
	}
	towerOfHanoi(n - 1, src, aux, dst);
	move(src, dst, n);
	towerOfHanoi(n - 1, aux, dst, src);
}

int
main(void) 
{
	/* open input & output files */
    fout = fopen(FILE_OUT, "w");
    towerOfHanoi(N, 'A', 'C', 'B');
	fclose(fout);

    return 0;
}
