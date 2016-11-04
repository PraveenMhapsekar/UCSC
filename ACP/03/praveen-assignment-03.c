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
/*    Assignment Number: 03                                                   */
/*                                                                            */
/*                                                                            */
/*    Topic: Chapter 6 (Array)                                                */
/*                                                                            */
/*    File name:  praveen-assignment-03.c                                     */
/*                                                                            */
/*    Date: 10/14/2016                                                        */
/*                                                                            */
/*    Objective: Program for array manipulation                               */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE    128
#define SUCCESS       0
#define ERROR        -1

#define PGM_ERR_MESSAGE(msg) fprintf(stderr, "%s:%d %s\n", __func__, __LINE__, #msg)

/* This function will recieve numbers from the stdin and store it in an array A[] and 
   display it back on stdout 
*/
int
processInput(int *A)
{
    int i = 0;
    char choice;

    /* read and validate array size  */
    while (1) {
        __fpurge(stdin);
        printf("Enter number? (y/n) : ");
        if ((scanf("%c", &choice) != 1) || ((choice != 'y') && (choice != 'n') && (choice != '\n'))) {
              printf("Invalid choice ! Please re-enter your choice\n"); 
              __fpurge(stdin);
              continue;
        }

        if (choice == 'n') {
              return i;
        }

        printf(" Enter the number : ");
        if (scanf("%d", &A[i]) != 1) {
              printf("Invalid number, please re-enter!!!\n"); 
              __fpurge(stdin);
              continue;
        }
        i++;
        if (i == MAX_SIZE) {
              printf("Array max size of %d reached, no more input accepted\n", MAX_SIZE);
        }
    }
}

/* Copy array from[] to to[] */
void
copyArray (int *from, int *to, int n)
{
    int i;
    for (i = 0; i < n; i++)
        to[i] = from[i];
}

/* Print an array */
void
printArray (int *A, int n)
{
    int i;
    for (i = 0; i < n; i++) 
        printf("%3d%c", A[i], (i < n - 1)? ',' : '.');
    printf("\n");
}

/* Print an array in reverse order */
void
printReverse (int *A, int n)
{
    int i;
    for (i = n-1; i >= 0; i--)
        printf("%3d%c", A[i], (i > 0)? ',' : '.');
    printf("\n");

}

/* Helper function for sorting
   swap contents of two pointers
*/
void 
swap (int *x, int *y) 
{
    if (x == y)   /* If contents to be swapped are same, return */
        return;
    *x = *x^*y;
    *y = *x^*y;
    *x = *x^*y;
}

/* Helper function for quickSort
   finding pivot
*/
int
findPivot(int low, int high, int *A)
{
    int pivot = A[low];
    int left = low;
    int right = high;

    while (left < right) 
    {
        while ((pivot >= A[left]) && (left < high))
            left++;
        while (A[right] > pivot)
            right--;
        if (left < right)
            swap(&A[left], &A[right]);
    }

    swap (&A[right], &A[low]);

    return right;
}

/* Quick sort */
quickSort(int low, int high, int *A) 
{
    int  pivot;

    if (low < high) {
        pivot = findPivot(low, high, A);
        quickSort(low, pivot - 1, A);
        quickSort(pivot + 1, high, A);
    }
}

/* Take input number from stdin and find its index in unsorted array
   if number is not found in an array, display message
 */
void
identifyIndices(int *A, int N) 
{
    char choice;
    int num;
    int i;
    int found;

    /* read and validate number of elements  */
    while (1) {

        __fpurge(stdin);
        printf("Do you want to enter number to get its index? (y/n) : ");
        if ((scanf("%c", &choice) != 1) || ((choice != 'y') && (choice != 'n'))) {
               printf("Invalid choice ! Please re-enter your choice\n"); 
              __fpurge(stdin);
              continue;
        }

        if (choice == 'n') {
              printf("Good bye!!!\n");
              return;
        }

        printf(" Enter the number : ");
        if (scanf("%d", &num) != 1) {
               printf("Invalid number ! Please re-enter correct number\n"); 
               __fpurge(stdin);
        } 

        found = 0;
        for (i = 0; i < N; i++) {
            if (num == A[i]) {
                found = 1;
                 printf ("Entered number %2d is at index %2d\n", num, i);
            }
        }

        if (!found)
            printf("Entered number %d is not present in the array\n", num);
    }
}

int
main ()
{
    int N;
    int A[MAX_SIZE];
    int B[MAX_SIZE];
    N = processInput(A);

    printf ("\nPrinting array in origional form:\n");
    printArray(A, N);

    printf ("\nPrinting array in reverse form:\n");
    printReverse(A, N);

    printf ("\nPrinting array in sorted form:\n");
    copyArray(A, B, N);
    quickSort(0, N - 1, A);
    printArray(A, N);
    identifyIndices(B, N);

    return SUCCESS;
}
