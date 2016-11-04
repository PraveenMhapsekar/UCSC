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
/*    Assignment Number: 01                                                   */
/*                                                                            */
/*                                                                            */
/*    Topic: Chapter  1 & 2                                                   */
/*                                                                            */
/*    File name:  praveen-assignment-01.c                                     */
/*                                                                            */
/*    Date: 10/14/2016                                                        */
/*                                                                            */
/*    Objective: Program for temperature conversion                           */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>

char *menuString[] = {
                      "",
                      "Fahrenehit",
                      "Centigrade",
                      };

typedef enum menuItem 
{
    fahren = 1,
    centig,
} menyItem_t;

#define PGM_ERR_MESSAGE(msg) fprintf(stderr, "%s:%d %s\n", __func__, __LINE__, #msg)

/* Print menu options
 * Accept and validate option and return it on function call stack 
 * Accept data to be convereted and returned via pointer (*data)
 */
int
menu(int *data)
{
    int op;
    printf("Menu:\n");
    printf(" %2d. %s to %s\n", fahren, menuString[fahren], menuString[centig]);
    printf(" %2d. %s to %s\n", centig, menuString[centig], menuString[fahren]);
    printf("Please enter your choice:");
    if ((scanf("%d", &op) != 1) || (op < fahren) || (op > centig)) {
        printf("Wrong menu option entered, Good Bye!!!\n"); 
        __fpurge(stdin);
        return -1;
    }
    printf("Please enter value of %s :", menuString[op]);
    if (scanf("%d", data) != 1) {
        printf("Wrong menu option entered, Good Bye!!!\n"); 
        __fpurge(stdin);
        return -1;
    }
    return op;
}

/* Convert & print Fahrenhit data to Centigrade */
void
fahrenhit2Centigrade (int F) 
{
    printf("Fahrenhit scale %d, equivalent Centigrade scale is %d\n", F, (((F -32) * 5)/9));
}

/* Convert & print Centigrade data to Fahrenhit */
void
centigrade2Fahrenhit (int C) 
{
    printf("Fahrenhit scale %d, equivalent Centigrade scale is %d\n", C, (((C * 9) / 5) + 32));
}

int
main(void) 
{
    int data;
    switch (menu(&data)) {
        case fahren:
            fahrenhit2Centigrade(data);
            break;
        case centig:
            centigrade2Fahrenhit(data);
            break;
        default:
            break;
    }

    return 0;
}
