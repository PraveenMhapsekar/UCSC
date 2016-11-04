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
/*    Assignment Number: 02                                                   */
/*                                                                            */
/*                                                                            */
/*    Topic: Chapter 2 (Loops)                                                */
/*                                                                            */
/*    File name:  praveen-assignment-02.c                                     */
/*                                                                            */
/*    Date: 10/14/2016                                                        */
/*                                                                            */
/*    Objective: Program for averaging student grades                         */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/
#include <stdio.h>
#include <limits.h>

#define MIN_STUDENT   1
#define MAX_STUDENT  16 
#define MAX_GRADE   100
#define MIN_GRADE     0
#define SUCCESS       0
#define ERROR        -1

#define PGM_ERR_MESSAGE(msg) fprintf(stderr, "%s:%d %s\n", __func__, __LINE__, #msg)

int
main ()
{
    int n;
    int i;
    int grade;
    float avg = 0;
    int min = INT_MAX;
    int max = INT_MIN;

    /* print menu */
    printf ("\bThis program support :\n"
            "\t- Max number of students %d\n"
            "\t- Student score in the range of %d to %d\n\n", MAX_STUDENT, MIN_GRADE, MAX_GRADE);

    /* read and validate number of students */
    while (1) {
        printf(" Enter the number of students : ");
        if ((scanf("%d", &n) != 1) || ((n < MIN_STUDENT) || (n > MAX_STUDENT))) {
            printf("Invalid number of students! Please re-enter correct number\n"); 
            __fpurge(stdin);
        } else {
           break;
        }
    }

    printf("\n");

    /* read score for each student and compute minimum, maximum and average */
    for (i = 1; i <= n; i++) {
        /* Read and validate score */
        printf("Enter score for the student #%2d : ", i);
        if ((scanf("%d", &grade) != 1) || (grade < MIN_GRADE) || (grade > MAX_GRADE)){
            printf("Invalid score, please re-enter!!!\n"); 
            __fpurge(stdin);
            i--;
            continue;
        }

        /* print read score */
        printf("Entered score for the student #%2d is %2d\n\n", i, grade);

        /* verify min */
        if (min > grade)
            min = grade;

        /* verify max */
        if (max < grade)
            max = grade;

        /* compute max */
        avg = ((avg * (i - 1)) + grade) / i ;
     }

    /* print computed minimum, maximum and average */
    printf("\nProcessing...\n");
    printf("Minimum of all students grade is %2d\n", min);
    printf("Maximum of all students grade is %2d\n", max);
    printf("Average of all students grade is %2.2f\n", avg);

    return SUCCESS;
}
