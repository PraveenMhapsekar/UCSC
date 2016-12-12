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
/*    Assignment Number: 12                                                   */
/*                                                                            */
/*    Topic: Sort                                                             */
/*                                                                            */
/*    File name:  praveen-assignment-12.c                                     */
/*                                                                            */
/*    Date: 12/09/2016                                                        */
/*                                                                            */
/*    Objective                                                               */
/*      Four simple sort routines ( Bubble sort, insertion sort, shell sort   */
/*		selection sort) are discussed in the course. Call the sort routines   */
/*		through the main routine with a menu. Again call one of the advanced  */
/*		sort options (Quicksort, Heapsort, Megersort).                        */
/*                                                                            */
/*		User will pick one among the choice sort routines from simple sorts   */
/*	   	and one from the advanced sort options.                               */
/*                                                                            */
/*		Read input from an input file directly as integers:                   */
/*		49, 17, 56, 85, 12, 97, 33, 71, 19, 62, 38, 84, 51,                   */
/*		29, 77, 65, 44, 99, 4, 47,67, 41, 23, 88, 73, 8, 100,                 */
/*		25, 91, 58, 59, 22, 15, 35, 95, 60, 20, 7, 50, 10                     */
/*                                                                            */
/*		Implement one of the above sort routines and show the results of the  */
/*		sort in the output.                                                   */
/*		                                                                      */
/*		Print the sorted output file for simple sort and advanced sort.       */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define NN 128

int N;
int A[NN];
int testArray[NN];
int AA[NN];

char
*menu [] = {
            "",
            "Bubble Sort", 
            "Selection Sort",
            "Insertion Sort",
            "Bucket sort",
            "Radix Sort",
            "Quick Sort",
            "Merge Sort",
            "Heap Sort"
            ""    
            };

typedef enum 
sortMenu {
            sortlistStart,
            bubblesort,
            selectionsort,
            insertionsort,
            bucketsort,
            radixsort,
            quicksort,
            mergesort,
            heapsort,
            sortListEnd,
          } sortMenu_t;

#define FILE_IN  "praveen-assignment-12-input.doc"
#define FILE_OUT "praveen-assignment-12-output.doc"

void
copyArry()
{

    FILE *finput; /* Input file pointer */
	FILE *fout;   /* Output file pointer */
	int  data;
    int  i = 0;

	/* Open input & output files */
    finput = fopen(FILE_IN, "r");
    fout = fopen(FILE_OUT, "w");

	fprintf(fout, "Data to be sorted :\n");
    while (fscanf(finput, "%d", &data) == 1) {
        A[i++] = data;
		fprintf(fout, "%d", data);
    }

	N = i + 1;
	fprintf(fout, "\n");
	fclose(finput);
	fclose(fout);
}

int
testSortArray() 
{
    int i;
    for (i = 0; i < N; i++) {
        if (A[i] != testArray[i]) {
            return 0;
        }
    }
    return 1;
}

void
printArray()
{
    int i;

	FILE *fout;   /* Output file pointer */
    fout = fopen(FILE_OUT, "w");

	fprintf(fout, "Sorted data :\n");
    for (i = 0; i < N; i++) {
        printf("%d ", A[i]);
		fprintf(fout, "%d ", A[i]);
    }
    printf("\n"); 
	fclose(fout);
}

void 
swap (int *a, int *b)
{
    if (a == b) {
        return;
    }

    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

/* 1. Bubble Sort ************************************************************************************************************/
void
bubbleSort() 
{
    int i, j; // Pass
    for (i = 0; i < N - 1;  i++) {
        for (j = 0; j < (N - i - 1); j++) {
            if (A[j] > A[j+1]) {
                swap(&A[j], &A[j+1]);
            }
        }
    }
}

/* 2. Selection Sort **********************************************************************************************************/
void
selectionSort() 
{
    int i, j;
    int key = 0;
    for (i = 0; i < N - 1; i++) {
        key = i; 
        for (j = i; j < N; j++) {
            if (A[j] < A[key]) {
                key = j;
            }
        }
        swap(&A[i], &A[key]);
    }
}

/* 3. Insertion Sort **********************************************************************************************************/
void
insertionSort()
{
    int i, j, temp;
    for (i = 1; i < N; i++) {
         for (j = i; j > 0; j--) {
            if (A[j] < A[j-1]) {
                swap (&A[j], &A[j-1]);
            }
        }
    }
}

/* 4. Quick Sort ************************************************************************************************************/
int
partition (int left, int right)
{
    int pivot = A[left];
    int L = left;
    int R = right;

    while (L < R)
    {
        while ((pivot >= A[L]) && (L < right))
            L++; // All the elements to the left of L are equal to or smaller than pivot.
        while (A[R] > pivot)
            R--; // All the elements to the right of R are greater than pivot, R is now pointing at element smaller than pivot, which is suppse to be left of pivot as per above comment
        if (L < R)
            swap(&A[L], &A[R]); // swap R and L and iterate again.
    }

    swap (&A[R], &A[left]); //Swap Pivot with smallest element 
    return R; // Return new Pivot;
}

int
quickSort (int left, int right)
{
    int pivot;

    if (left < right) {
        pivot = partition(left, right);
        quickSort(left, pivot - 1);
        quickSort(pivot + 1, right); 
    }
}

/* 5. Merge Sort ************************************************************************************************************/
void
merge(int l, int m, int r) 
{
    int i = 0;
    int j = 0;
    int k = 0;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for(i = 0; i < n1; i++) {
        L[i] = A[l+i];
    }

    for(j = 0; j < n2; j++) {
        R[j] = A[m+1+j];
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;    
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }
      
    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }
}

void 
mergeSort(int start, int end) 
{
   int mid;

   if (start >= end) {
       return;
   }

   mid = (start + (end - 1))/2;

   mergeSort(start, mid);
   mergeSort(mid + 1, end);
   merge(start, mid, end);

   return;
}

/* 6. Heap Sort ************************************************************************************************************/
/*
 * n -> heap size
 * i -> index
 */
void 
heapify (int n, int i) 
{
   int largest = i;    /* Root        */
   int lc = i * 2 + 1; /* Left child  */
   int rc = i * 2 + 2; /* Right child */
  
   if ((A[largest] < A[lc]) && (lc < n)) {
        largest = lc;
   }

   if ((A[largest] < A[rc]) && (rc < n)) {
        largest = rc;
   }

   if (i != largest) {
       swap (&A[i], &A[largest]); /* New root          */
       heapify(n, largest);       /* Heapify new child */
   }
}

void
heapSort()
{
    int i;
  
    /* Build heap from initial array */ 
    for (i = (N/2) - 1; i >= 0; i--) {
        heapify(N, i);
    }

    /* Extract elements from the heap in sorted manner */
    for (i = N - 1; i >= 0; i--) {
        swap (&A[i], &A[0]); /* Extract heighest element and swap/store at the end of the array */
        heapify(i, 0);       /* Heapify new root */
    } /* Reduce array size (i--) */
}

/* 7. Bucket Sort ***********************************************************************************************************/
#define BUCKET 256 // Asuming that all the elements are in the range (0 - (BUCKET - 1))
void
bucketSort()
{
    int i;
    int k = 0;
    int BA[BUCKET];

    for (i = 0; i < BUCKET; i++) 
        BA[i] = 0;

    for (i = 0; i < N; i++) 
        BA[A[i]]++;
        
    for (i = 0; i < BUCKET; i++) {
        while (BA[i]) {
            A[k++] = i;
            BA[i]--;
        }
    }
}

/* 8. Counting Sort ************************************************************************************************************/
void
countingSort(int n, int exp, int COUNT) 
{
    int i;
    int k = 0;

#define IDX (A[i]/exp)%10
    int count[COUNT];
    int output[n];

    /* Clear count array */
    for (i = 0; i < COUNT; i++) {
        count[i] = 0;
    }

    /* Count & store the number of numbers matching 'divide by exp' */
    for (i = 0; i < n; i++) {
        count[IDX]++;
    }

    /* Get cumulative count */
    for (i = 1; i < 10; i++) {
        count[i]+= count[i - 1];
    }

    /* build array by placing numbers from the end */
    for (i = (n - 1); i >= 0; i--) {
        output[count[IDX] - 1] = A[i]; /*These two line are important to understand the logic */
        count[IDX]--;
    }

    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++) {
        A[i] = output[i];
    }
}

/* 9. Radix Sort ************************************************************************************************************/
void
radixSort()
{
    int i, exp;
    int max = INT_MIN;

    for (i = 0; i < N; i++) {
        if (A[i] > max) {
            max = A[i];
        }
    }

    for (exp = 1; (max/exp) > 0; exp = (exp * 10)) {
        countingSort(N, exp, 10);
    }
}

/***************************************************************************************************************************/
void
printMenu ()
{
    sortMenu_t i;
    printf("\n\nMenu:\n");
    for (i = sortlistStart + 1; i < sortListEnd; i++) {
          printf("%2d. %-15s", i, menu[i]);
          if (((i % 5) == 0) || (i == sortListEnd - 1)) { /* Print 5 menu items per line */
              printf ("\n");
          }
    }
    printf ("Enter your choice :\n");
}

int
getChoice(sortMenu_t *cc) 
{
    int n, c;

    if (((n = scanf("%d", &c)) != 1) || (c > sortListEnd) || (c < bubblesort)) {
        printf ("\nWrong input!!!\nPlease get familiar with menu options to run this program\nGood Bye for now!!!\n");
        return 0;        
    }

    *cc = c;
    return 1;
}

int
main (void)
{
    sortMenu_t c;

    printMenu();

    while (1) {
        if (getChoice(&c) == 0) {
            return 0; 
        }        

        copyArry();  // Read unsorted array into to be sorted array A[]
        printf("Your want to use %s\nArray to be sorted is...\n", menu[c]);
        printArray();
        printf("%s...\n", menu[c]);

        switch (c) {
            case bubblesort:
                bubbleSort();
                printArray();
                break;
            case selectionsort:
                selectionSort();
                printArray();
                break;
            case insertionsort:
                insertionSort();
                printArray();
                break;
            case mergesort:    
                mergeSort(0, (N-1));
                printArray();
                break;
            case bucketsort:
                bucketSort();
                printArray();
                break;
            case quicksort:
                quickSort(0, N-1);
                printArray();
                break;
            case heapsort:
                heapSort();
                printArray();
                break;
            case radixsort:
                radixSort();
                printArray();
                break;
            default:
                printf ("\bYour choice %s not yet implemeneted\n", menu[c]);   
                printMenu();
                continue;
        }
#ifdef TEST_YOUR_WORK
        // Test sorted array aginst expected results
        if (!testSortArray()) {
             printf("\n\n\b\b Error sorting failed\n");
        }
#endif
        // Print menu for next execution option
        printMenu(); 
    }

    return 0;
}
