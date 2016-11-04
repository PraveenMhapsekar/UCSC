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
/*    Assignment Number: 04                                                   */
/*                                                                            */
/*                                                                            */
/*    Topic: Chapter 10 (Function)                                            */
/*                                                                            */
/*    File name:  praveen-assignment-04.c                                     */
/*                                                                            */
/*    Date: 10/16/2016                                                        */
/*                                                                            */
/*    Objective: Student grade processing                                     */
/*                                                                            */
/*    Comments: Write your comments or questions in red                       */
/******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SUCCESS       0
#define ERROR        -1

/* input file containing student score data */
#define INFILE "praveen-assignment-04-input.doc"
/* output file containing class report      */
#define OUTFILE "praveen-assignment-04-output.doc"

/* structure for storing student score and corrosponding grades per subject */
typedef struct subject_record {
    int  score;
    char *grade;
} subject_record_t;

/* Student record */
typedef struct student_record {
    int studentId;             /* student id                             */
    subject_record_t *subject; /* pointer to array of per subject record */
    int minScore;              /* minimum score                          */
    int minScoreSubject;       /* subject index of minimum score         */
    int maxScore;              /* maximum score                          */
    int maxScoreSubject;       /* subject index of maximum score         */
    int average;               /* student score average                  */
    char *averageGrade;        /* student grade as per average score     */
} student_record_t;

/* class record */
typedef struct class_record {
    student_record_t *student; /* Array of student records        */
    int numStudent;            /* number of students in the class */
    int numSubject;            /* number of subjects per student  */
} class_record_t;

/* student id seed */
const static int studentId = 1000;

#ifdef STDIN
/* helper function to create input file from standard input */
void createDataFile()
#endif

/* process score and return character grade */
char* assignGrade(int score);
/* function to process input file and
   return number of students in the class &
   number of students per class */
int processInput(int *subjectPerStudent);
/* function to read and process data from input file */
class_record_t * processData(int numStudent, int numSubjects);
/* function to print student report */
void printStudentRecord(class_record_t *class, int id, FILE *outFile);
/* function to print class report */
void printClassReport(class_record_t *class);
/* function to free all memory */
class_record_t * cleanUp(class_record_t *class);

/* main function */
int
main(void)
{
    int numStudent;   /* number of students in the class     */
    int numSubjects;  /* number of subjects per student      */
    class_record_t *class = NULL; /* pointer to class record */

#ifdef STDIN  
    /* optionally, create input data file from stdin */
    createDataFile();
#endif    

    /* read input to determine number of students & subjects per student */
    numStudent = processInput(&numSubjects);
    if (numStudent == ERROR) {
        goto error;
    }

    /* read data from input file and proces and store it in class record */
    class = processData(numStudent, numSubjects);
    if (!class) {
        goto error;
    }

    /* print class report for the class */
    printClassReport(class);

    /* clean up all memory allocation */
    class = cleanUp(class);

    return(SUCCESS);

error:
    class = cleanUp(class);
    fprintf (stderr, "Program error\n");
    return ERROR;
}

#ifdef STDIN
/*   This is helper function to create input data file from stdin input */
void
createDataFile()
{
    FILE *outFile;
    outFile = fopen(INFILE, "w");
    char choice;
    int n;

    while (1) {
        __fpurge(stdin);
        printf("Enter number? (y/n) : ");
        if ((scanf("%c", &choice) != 1) || ((choice != 'y') && (choice != 'n') && (choice != '\n'))) {
              printf("Invalid choice ! Please re-enter your choice\n"); 
              __fpurge(stdin);
              continue;
        }

        if (choice == 'n') {
              fclose(outFile);
              return;
        }

        printf("Enter the number : ");
        if (scanf("%d", &n) != 1) {
              printf("Invalid number, please re-enter!!!\n"); 
              __fpurge(stdin);
              continue;
        }
        fprintf(outFile, "%3d,", n);
    }
}
#endif

/* this function will map score to grade */
char*
assignGrade(int score)
{
    char *grade = NULL;

    grade = malloc(3);
    if (grade == NULL) {
        fprintf(stderr, "%s:%d Memory allocation failed\n", __func__, __LINE__);
        return grade;
    }

    if (score > 95)
        return(strcpy(grade, "A+"));
    if (score == 95)
        return(strcpy(grade, "A"));
    if (score >= 90)
        return(strcpy(grade,"A-"));
    if (score > 85)
        return(strcpy(grade,"B+"));
    if (score == 85)
        return(strcpy(grade,"B"));
    if (score >= 80)
        return(strcpy(grade,"B-"));
    if (score > 75)
        return(strcpy(grade,"C+"));
    if (score == 75)
        return(strcpy(grade,"C+"));
    if (score >= 70)
        return(strcpy(grade,"C-"));
    if (score >= 60)
        return(strcpy(grade,"D"));

    return(strcpy(grade,"F"));
}

/* This function will accept input from then user indicating number of students in the class/input file
   This function will walkthrough input file, calculate and return number of subjects per student */
int
processInput(int *subjectPerStudent)
{
    int count = 0;
    int n;
    char c;
    int numStudent = 0;
    int err;
    FILE *inFile = NULL;

    while(1) {
        printf("Enter the number student (4-6) :");
        if ((scanf("%d", &numStudent) == 1) && (numStudent >= 4) && (numStudent <= 6)) {
              break;
        } 
        printf("Invalid number, please re-enter!!!\n"); 
        __fpurge(stdin);
    }

    inFile = fopen(INFILE, "r+");
    if (!inFile) {
        printf("Error opening file\n");
        return ERROR;
    }

    while (err != EOF) {
        err = fscanf(inFile, "%d%c", &n, &c); 
        if (err == 2) {     
            count++;
        } 
    }

    *subjectPerStudent = count / numStudent;
    fclose(inFile);

    return numStudent;
}

/* this function will read data from the input file and process it and store results into class record */
class_record_t *
processData(int numStudent, int numSubjects)
{
    int i;
    int j;
    char c;
    int marks;
    FILE *inFile;
    int err = INT_MIN;
    class_record_t *class = NULL;

    /* create & init class record */
    class = malloc(sizeof(class_record_t));
    if (!class) {
        fprintf(stderr, "%s:%d Memory allocation failed\n", __func__, __LINE__);
        return class;
    }
    class->student = NULL;
    class->student = malloc(sizeof(student_record_t) * numStudent);
    if (!class->student) {
        fprintf(stderr, "%s:%d Memory allocation failed\n", __func__, __LINE__);
        return (cleanUp(class));
    }

    class->numStudent = numStudent;
    class->numSubject = numSubjects;    

    inFile = fopen(INFILE, "r");

    /* for each student ... */
    for (i = 0; i < numStudent; i++) {
        /* init student records */
        class->student[i].studentId = studentId + i;
        class->student[i].subject   = NULL;
        class->student[i].subject   = malloc(sizeof(subject_record_t) * numSubjects);
        if (!class->student[i].subject) {
            fprintf(stderr, "%s:%d Memory allocation failed\n", __func__, __LINE__);
            return (cleanUp(class));
        }
        class->student[i].minScore  = INT_MAX;
        class->student[i].maxScore  = INT_MIN;
        class->student[i].average   = 0;
        class->student[i].averageGrade = "";

        /* for each subject ... */
        for (j = 0; j < numSubjects; j++) {
            err = fscanf(inFile, "%d%c", &marks, &c);
            if (err == 2) {
                /* store score and corrsponding grade for the subject */
                class->student[i].subject[j].score = marks;
                class->student[i].subject[j].grade = assignGrade(marks);

                /* compute maximum score for the student */
                if (class->student[i].subject[j].score > class->student[i].maxScore) {
                    class->student[i].maxScore = class->student[i].subject[j].score;
                    class->student[i].maxScoreSubject = j;
                }

                /* compute minimum score for the student */
                if (class->student[i].subject[j].score < class->student[i].minScore) {
                    class->student[i].minScore = class->student[i].subject[j].score;
                    class->student[i].minScoreSubject = j;
                }

                /* compute average score for the student */
                class->student[i].average = ((class->student[i].average * j) + marks) / (j + 1);
                class->student[i].averageGrade = assignGrade(class->student[i].average);
            } else {
                fclose(inFile);
                return class;
            }
        } /* end of numSubjects for loop */
    } /* end of numStudent for loop */

    fclose(inFile);
    return class;
}

/* print student report */
void
printStudentRecord(class_record_t *class, int id, FILE *outFile) 
{
    int j;
     
    fprintf(outFile, "\nStudent Id : %4d\n"
           "MaximumScore %d in subject[%d]\n"
           "MinimumScore %d in subject[%d]\n"
           "AverageScore is %3d AverageGrade is %s\n", 
           class->student[id].studentId, 
           class->student[id].minScore, class->student[id].minScoreSubject, 
           class->student[id].maxScore, class->student[id].maxScoreSubject, 
           class->student[id].average, class->student[id].averageGrade); 

    for (j = 0; j < class->numSubject; j++) {
        fprintf(outFile, "Subject[%d] - %3d grade %s\n", j, class->student[id].subject[j].score, class->student[id].subject[j].grade);
    }
}

/* print class report */
void
printClassReport(class_record_t *class) 
{
    int i;
    FILE *outFile;

    outFile = fopen(OUTFILE, "w+"); 
    fprintf(outFile, "Number of students = %2d\nNumber of subjects = %2d\n", class->numStudent, class->numSubject);
    for (i = 0; i < class->numStudent; i++)
        printStudentRecord(class, i, outFile);
    fclose(outFile);
}

/* free allocated memory */
class_record_t *
cleanUp(class_record_t *class)
{
    int i;
    int j;
    if (!class)
        return NULL;
    for (i = 0; i < class->numStudent; i++) {
        for (j = 0; j < class->numSubject; j++) {
            if (!class->student) 
                continue;
            if (class->student[i].subject) 
                continue;
            if (!class->student[i].subject[j].grade) 
                continue;
            free(class->student[i].subject[j].grade);
            class->student[i].subject[j].grade = NULL;
        } /* end of for(numSubject) */
        if (!class->student[i].subject)
            continue;
        free(class->student[i].subject);
        class->student[i].subject = NULL;
    } /* end of for(numStudent) */

    if (class->student) {
        free(class->student);
        class->student = NULL;
    }

    free(class);
    return NULL;
}
