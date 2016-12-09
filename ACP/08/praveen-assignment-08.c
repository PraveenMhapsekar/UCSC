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
/*    Assignment Number: 08                                                   */
/*                                                                            */
/*    Topic: Stack                                                            */
/*                                                                            */
/*    File name:  praveen-assignment-08.c                                     */
/*                                                                            */
/*    Date: 11/18/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*    Evaluate the validity of the scopes in the following expression         */
/*    implementing stacks. Ignore the operators and operand in the expression */
/*    while checking the validity of the expression.                          */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include "stack.h"

#define FILE_IN  "praveen-assignment-08-input.doc"
#define FILE_OUT "praveen-assignment-08-output.doc"

void
inputFileProcessing()
{
    FILE *finput;
	FILE *fout;
    stack_t *S;
    char token;

	/* Open input & output files */
    finput = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT, "w");

	/* Create stack */
    createStack(&S, sizeof(char));     

    while ((token = fgetc(finput)) != EOF) {
        fprintf(fout, "Token '%c' - action ", token);
        switch (token) {
            case '{' :
            case '(' :
            case '[' :    
				/* Print action and Push opening bracket to the stack */
                fprintf(fout, "Push\n");
                push(S, &token);
                break;
            case '}' :
            case ')' :
            case ']' :    
				/* Print action and pop matching opening brackets from the stack */
                fprintf(fout, "Pop\n");
                if (!pop(S, &token)) {
					/* Stack empty, without matching closing bracket */
                    fprintf(fout, "equation is not correct\n");
                }
                break;
            default:
				/* Ignore any other symbols than opening/closing brackets */
                fprintf(fout, "Ignore\n");
                break;
        }
        fflush(stdout);
    }

	/* Check if stack is empty at the end of symbols processing */
    if (!pop(S, &token))
		/* If stack is empty, that means all opening and closing symbols matched */
        fprintf(fout, "\nEquation is correctly formatted\n");
    else
		/* Stack is not empty, there was mismatch between opening/closing symbols */
        fprintf(fout, "\nEquation is not in correct format\n");

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
