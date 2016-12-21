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
/*        and other required.                                                 */
/*        Read the input into a buffer from input file.                       */
/*        Place a space between numbers and operators, numbers and numbers,   */
/*        and operators and operators. (Note: Do not initialize an array with */
/*        input values.). Convert the following expression from infix notation*/ 
/*        to prefix notation.                                                 */
/*                                                                            */
/*    Expression:                                                             */
/*        (25 % 7 * 8) / (75 / 5 - 8 + (2 ^ 4 - (2 ^ 2 + 16) + 16 - 3)        */
/*         + 5 - 3 ^ 2)                                                       */
/*                                                                            */
/*        Using an array structure read the numbers from an input file.       */
/*        Print the original infix notation                                   */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "stack.h"

#define FILE_IN  "praveen-assignment-17-input.doc"
#define FILE_OUT "praveen-assignment-17-output.doc"

char operator[7] = {'*','/','%','+','-','^'};
char precedence[7] = {3,3,3,4,4,9};

/*
 * Check precedence between X and Y
 *  return 1 if precedence(X) < precedence(y)
 *  return 0 otherwise
 */
char
checkPrecedance(char X, char Y)
{
    int i;
    char xPre = 0;
    char yPre = 0;
    for (i = 0; i <= 6; i++) {
        if (X == operator[i]) {
            xPre = precedence[i];
            break;
        }
    }

    for (i = 0; i <= 6; i++) {
        if (Y == operator[i]) {
            yPre = precedence[i];
            break;
        }
    }

    if (xPre < yPre) {
        return 1;
    }
    return 0;
}

/* 
 *  Check if given token is opernad
 */ 
bool
isOperand (char token) 
{
    if (((token >= '0') && (token <= '9')) ||
        ((token >= 'a') && (token <= 'z')) ||
        ((token >= 'A') && (token <= 'Z'))) {
        return true;
    } else {
        return false;
    }
}

/* 
 *  Check if given token is operator
 */ 
bool
isOperator(char token)
{
    if ((token == '+') || 
        (token == '-') ||
        (token == '/') ||
        (token == '*'))
      return true;
   else
      return false;
}   

/* 
 *  eadck if given token is opernad
 */ 
void
inputProcessing()
{
    char token;
    char str[3];
    char tmp;
    FILE *fin;
    FILE *fout;
    stack_t *S;
    stack_t *I;
    stack_t *P; /* Operator stack */
    int len, k = 0;
    createStack(&I, sizeof(char)); 
    createStack(&S, sizeof(char)); 
    createStack(&P, sizeof(char)); 
    /* Open input & output files */
    fin  = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT,"w");

    fprintf(fout, "\nRead expresseion from input file and print it\n");
    while ((fscanf(fin, "%s", str) == 1)) {
        k = 0;
        len = strlen(str);
        while (len) {
            token = str[k++];
            len--;
            fprintf(fout, "%c", token);
          //  if (token != ' ')
               push(I, &token);
        }
        token = ' ';
        push(I, &token);
        fprintf(fout, "%c", token);
    }

    fprintf(fout, "\n\n");

    /* Read token from file and process it */
    while (!isEmptyStack(I)) {
        pop(I, &token);

        switch (token) {
            case ')' : push(S, &token);
                       break;
            case '(' :
                      while (!isEmptyStack(S)) {
                          pop(S, &tmp);
                          if (tmp == '(')
                              break;
                          else
                             push(P, &tmp);    
                      }
                      break;
            case '+' :
            case '-' :
            case '/' :
            case '*' :
            case '^' : 
            case '%' :          
                      while (!isEmptyStack(S)) {
                          peek(S, &tmp);
                          if (checkPrecedance(token, tmp)) {
                              pop(S, &tmp);
                              push(P, &tmp);
                          } else {
                              break;
                          }
                      }
                      push(S, &token);    
                      break;
            case ' ' :    
                      push(P, &token);
                      break;
            default  :
                      if(isOperand(token)) {
                          push(P, &token);
                      }           
        }
    }

    fprintf(fout, "\nPrefix output is\n");
    while(!isEmptyStack(P)) {
         pop(P, &tmp);
         if (tmp != ')')
         fprintf(fout, "%c", tmp);
    }     

    fprintf(fout, "\n\n\n");

    /* Close files */
    fclose(fin);
    fclose(fout);
}

int
main(void) 
{
    inputProcessing();
    return 0;
}
