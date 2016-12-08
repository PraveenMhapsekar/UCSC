#ifndef __STACK_H__
#define __STACK_H__

typedef enum dataType {
    signedchar,
    unsignedChar,
    signedShort,
    unsignedShort,
    unsignedInt,
    signedInt,    
    unsignedLong,
    signedLong,
    voidType,
    dataTypeEnd,
} dataType_t;

typedef struct frame {
    char *pData; 
    struct frame *nxt;
} frame_t;

typedef struct stack {
    int size;
    int frameSize;
    frame_t *top;
} stack_t;

int createStack(stack_t **, int);
int destroyStack(stack_t **);
int push(stack_t *, char *);
int pop(stack_t *, char *);

#endif
