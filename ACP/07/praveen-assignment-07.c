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
/*    Assignment Number: 07                                                   */
/*                                                                            */
/*    Topic: Backtracking                                                     */
/*                                                                            */
/*    File name:  praveen-assignment-07.c                                     */
/*                                                                            */
/*    Date: 12/03/2016                                                        */
/*                                                                            */
/*    Objective: N-Queen                                                      */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define N 8

int rowArray[N];
int rowPrintArray[N];
int cnt;
int inputColNumTracker;

void
clearColumn() 
{
    int i;

    for (i = 0; i < N; i++) {
       rowArray[i] = 0xF;
       rowPrintArray[i] = 0xF;
    }
}

void
copyarray()
{
    int i;
    for (i = 0; i < N; i++) {
       rowPrintArray[i] = rowArray[i];
    }
}

void 
print()
{
    int i, j;
    int n = N;
    printf("%1d-Queen Solution #%02d:\n", n, cnt++);
    printf("%c ", '*');

    for (i = 0; i < n; i++) {
        printf("%d ",i);
    }

    for (i = 0; i < n; i++) {
        printf("\n%d ",i);
        for (j = 0; j < n; j++) {
            if (rowPrintArray[i] == j) {
                printf("Q "); 
            } else {
                printf(". "); 
            }
        }
    }

    printf("\n\n");
}

void
printA(int c, int r)
{
    int i;

    for (i = 0; i < N; i++) {
        printf("%x ", rowArray[i]);
    }
    printf("\n");

    printf("%s  col %d  row %d \n", __func__, c, r);
}

int 
validate(int c, int r)
{
    int i;
    
    for (i = 0; i < c; i++) {
        if (rowArray[i] == r) {
            return 0;
        } else {
            if (abs(rowArray[i] - r) == abs(i - c)) {
                return 0;
            }
        }
    }

    return 1; 
}

void 
placeQueen(unsigned int col, unsigned int endCol, int n)
{
    int row = 0;

    for (row = 0; row < n; row++) {
        if (validate(col, row)) {
            rowArray[col] = row; 
            if (col == endCol) {
                copyarray();
                //  print();
                /* Commenting out exit will print all solutions */
                // exit (0);
                return;
            } else {            
                placeQueen((col + 1) % N, endCol, n);
            }
        }
    }
}

void 
placeQueenDriver(unsigned int col, int n)
{
    int row = 0;

    printf("Initial queen is placed in column %d row %d\n", col, row);
    clearColumn();

    placeQueen(col, (col - 1)%N, n);
    print();
}

bool
inputValidator(int col) 
{
    if (inputColNumTracker & (1 << col)) {
        return true;
    } else {
        inputColNumTracker = inputColNumTracker | (1 << col);
        return false;
    }
}

int 
main()
{
    int inputCount = 0;
    char choice;
    int col;
    unsigned int i;

    while (inputCount < N) {
        __fpurge(stdin);
        printf ("Enter initial row number:");

        if (scanf("%d", &col) != 1) {
              printf("Invalid row number, please re-enter!!!\n"); 
              continue;
        } else {

           if ((col < 0) || (col > (N -1))) {
              printf("Invalid row number, please re-enter!!!\n"); 
              continue;
           }

           if (inputValidator(col)) {
              printf("Column #%d already entered, please try another rowArray!\n", col); 
              continue;
           }

           inputCount++;  
           placeQueenDriver(col, N);

            while (1) {
                __fpurge(stdin);
                printf("Do you want to continue? (y/n) : ");
                if ((scanf("%c", &choice) != 1) || ((choice != 'y') && (choice != 'n') && (choice != '\n'))) {
                      printf("Invalid choice ! Please re-enter your choice\n"); 
                      continue;
                } else {
                      break;
                }
            }

            if (choice != 'y') {
                break;
            }
        }
    }

    return 0;
}
