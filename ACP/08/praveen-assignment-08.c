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
/*    Topic: Chapter 07 Stack                                                 */
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

void
fileProcessing()
{
    stack_t *S;
    char n;
    FILE *fp;
    char token;
    char tempToken;

    fp = fopen("praveen-assignment-08-input.doc", "r");
    createStack(&S, sizeof(n));     

    while ((token = fgetc(fp)) != EOF) {
        printf("\nToken '%c' Action ", token);
        switch (token) {
            case '{' :
            case '(' :
            case '[' :    
                printf("push\n");
                push(S, &token);
                break;
            case '}' :
            case ')' :
            case ']' :    
                printf("pop\n");
                if (!pop(S, &tempToken)) {
                    printf("equation is not correct\n");
                }
                break;
            default:
                printf("ignore\n");
                break;
        }
        fflush(stdout);
    }
    if (!pop(S, &tempToken))
        printf("equation is correct\n");
    else
        printf("equation is not correct\n");
    fclose(fp);
}

int
main(void) 
{
    fileProcessing();
    return 0;
}
