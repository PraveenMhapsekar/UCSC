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
/*    Assignment Number: 05                                                   */
/*                                                                            */
/*                                                                            */
/*    Topic: Chapter 10 (Function)                                            */
/*                                                                            */
/*    File name:  praveen-assignment-05.c                                     */
/*                                                                            */
/*    Date: 10/18/2016                                                        */
/*                                                                            */
/*    Objective: Pointer assignment                                           */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int
main (void)
{
    int     myInt        = 25;
    int    *myIntPtr     = &myInt;

    float   myFloat      = 3.142;
    float  *myFloatPtr   = &myFloat; 

    double  myDouble     = 1.73217;
    double *myDoublePtr  = &myDouble;

    char    myString[20] = "Hello C programmer";
    char   *myStringPtr  = myString;  

    char    myChar       = 'X';
    char   *myCharPtr    = &myChar;

    /* print integer */
    printf ("Address of varible myInt       : %p\n", &myInt);
    printf ("value   of varible myInt       : %d\n", myInt);
    printf ("Address of pointer myIntPtr    : %p\n", &myIntPtr);
    printf ("value   at pointer myIntPtr    : %p\n", myIntPtr);
    printf ("Deref value of ptr myIntPtr    : %d\n\n", *myIntPtr);

    /* print float */
    printf ("Address of varible myFloat     : %p\n", &myFloat);
    printf ("value   of varible myFloat     : %3.3f\n", myFloat);
    printf ("Address of pointer myFloatPtr  : %p\n", &myFloatPtr);
    printf ("value   at pointer myFloatPtr  : %p\n", myFloatPtr);
    printf ("Deref value of ptr myFloatPtr  : %3.3f\n\n", *myFloatPtr);

    /* print double */
    printf ("Address of varible myDouble    : %p\n", &myDouble);
    printf ("value   of varible myDouble    : %1.5f\n", myDouble);
    printf ("Address of pointer myDoublePtr : %p\n", &myDoublePtr);
    printf ("value   at pointer myDoublePtr : %p\n", myDoublePtr);
    printf ("Deref value of ptr myDoublePtr : %1.5f\n\n", *myDoublePtr);

    /* print string */
    printf ("Address of varible myString    : %p\n", &myString);
    printf ("value   of varible myString    : %s\n", myString);
    printf ("Address of pointer myStringPtr : %p\n", &myStringPtr);
    printf ("value   at pointer myStringPtr : %p\n", myStringPtr);
    printf ("Deref value of ptr myStringPtr : %s\n\n", (char *)(myStringPtr));

    /* print char */
    printf ("Address of varible myChar      : %p\n", &myChar);
    printf ("value   of varible myChar      : %c\n", myChar);
    printf ("Address of pointer myCharPtr   : %p\n", &myCharPtr);
    printf ("value   at pointer myCharPtr   : %p\n", myCharPtr);
    printf ("Deref value of ptr myCharPtr   : %c\n\n", *myCharPtr);

    return 0;
}

