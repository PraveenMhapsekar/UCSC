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
/*    Assignment Number: 06                                                   */
/*                                                                            */
/*    Topic: Tic-Tac-Toe                                                      */
/*                                                                            */
/*    File name:  praveen-assignment-06.c                                     */
/*                                                                            */
/*    Date: 11/06/2016                                                        */
/*                                                                            */
/*    Objective: Array Manipulation                                           */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include <string.h>

/* Tic-Tac-Toe grid size  */
#define N 4

/* Tic-Tac-Toe play array */
char A[N][N];

/* Default symbol */
#define DASH '-'

#define TRUE  1
#define FALSE 0

/* Player 0 will use 'O' symbol
   player 1 will use 'X' symbol */
#define PLAYER (player == 0 ? 'O' : 'X')  

/* Clear play array */
void 
clear ()
{
    int i, j;
    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            A[i][j] = DASH;
}

/* Display play array */
void 
display ()
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf ("%c ", A[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

/* Check if move is valid */
int
checkValidMove (int row, int column) 
{
    /* Check if move exceeds array size */
    if ((row > N-1) || (column > N-1)) 
        return FALSE;
    if ((row < 0) || (column < 0)) 
        return FALSE;

    /* If [row][colum] is unoccupied return TRUE */
    if (A[row][column] == DASH)
        return TRUE;

    return FALSE;
}

/* Verify Reverse diagonal for the winner */
int checkReverseDiag()
{
    int i, j;
    /* Take top right element */
    char key = A[0][N-1];

    /* If top right element is still unoccupied, 
       no winner in reverse diagonal */
    if (key == DASH)
        return FALSE;

    for (i = 0; i < N; i++) 
        for (j = 0; j < N; j++) 
            /* reverse diagonal is represented by elements[i][j], 
               such that i + j equal to N - 1 */
            if ((i + j) == (N - 1)) 
                if (key != A[i][j]) 
                    return FALSE;
    return TRUE;
}

/* Verify  diagonal for the winner */
int checkDiag()
{
    int i, j;
    /* Pick array element at [0][0] as first element of the diagonal */
    char key = A[0][0];

    /* If first element is still unoccupied, no winner in diagonal */
    if (key == DASH) 
        return FALSE;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (i == j) {
                if (key != A[i][j]) 
                    return FALSE;
            }
         }
    }    
    return TRUE;
}

/* Check winner */
int
checkWinner()
{
    int i, j;

    /* Check rows */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (A[i][j] == DASH) {
                /* If row element is still unoccupied, 
                   no winner in this row, skip this row */
                break;
            } else {
                if (A[i][j] != A[i][(j+1)%(N-1)]) {
                     /* If current row element is not same as next row element, 
                        no winner in this row, skip this row */
                     break;
                }
                if (j == N-1) {
                     /* We made it to the end of the row, 
                        This means, all the elements in this row are same 
                        declare and display winner */
                     printf ("Player %c is winner !!!\n", A[i][j]);
                     display();
                     return TRUE;
                }
            }
        }
    }

    /* Check Column */
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            if (A[i][j] == DASH) {
                /* If column element is still unoccupied, 
                   no winner in this column, skip this column */
                break;
            } else {
                if (A[i][j] != A[(i+1)%(N-1)][j]) {
                     /* If current column element is not same as next column element, 
                        no winner in this column, skip this column */
                     break;
                }
                if (i == N-1) {
                     /* We made it to the end of the column, 
                        This means, all the elements in this column are the same 
                        declare and display winner */
                     printf ("Player %c is winner !!!\n", A[i][j]);
                     display();
                     return TRUE;
                }
            }
        }
    }

    /* Check diagonal for the winner */
    if (checkDiag()) {
        printf ("Player %c is winner !!!\n", A[0][0]);
        display();
        return TRUE;
    }

    /* Check reverse diagonal for the winner */
    if (checkReverseDiag()) {
        printf ("Player %c is winner !!!\n", A[0][N-1]);
        display();
        return TRUE;
    }

    printf ("No winner yet, keep playing\n");
    return FALSE;
}

/* Is play array full? */
int
isFull() 
{
    int i, j;

    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++) 
            if (A[i][j] == DASH) 
                /* element is still unoccupied */
                return FALSE;
    return TRUE;
}

int
main(void) 
{  
    int player = 0;
    int row, col;

    /* Clear play array */
    clear();

    /* Display array before starting game */
    display();

    /* Prompt player to start the game */
    printf("Please enter value for row and column in the range of 0 - %d\n", N - 1);
    while (1) {
        /* Accept input for row number */
        while (1) { 
            printf("Player %c row?    :", PLAYER);
            if (scanf("%d", &row) == 1) {
                break;
            } else {
                __fpurge(stdin);
                printf("Please enter value for row and column in the range of 0 - %d\n", N - 1);
            } 
        }

        /* Accept input for column number */
        while (1) {
            printf("Player %c column? :", PLAYER);
            if (scanf("%d", &col) == 1) {
                break;
            } else {
                __fpurge(stdin);
                printf("Please enter value for row and column in the range of 0 - %d\n", N - 1);
            }
        }

        /* Validate <row, col> numbers and validate winner for cureent move*/
        if (checkValidMove(row, col)) {
            A[row][col] = PLAYER;
            display();
            if (checkWinner()) {
                return 0;
            }
        } else {
            printf ("Wrong move, reneter data\n");
            continue;
        }

        /* Verify if game is over */
        if (isFull()) {
            printf ("Game draw\n");
            break;
        }
       
        /* Change player for next move */ 
        player = (player + 1) % 2;
   } /* end of main while loop */

   return 0;
}
