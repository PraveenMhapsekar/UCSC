#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

char *dataTypeArr[dataTypeEnd] = {"signed char", "unsigned char", "signed short", "unsigned short", "signed int", "unsigned int", "signed long", "unsigned long", "void"};

int 
createStack(stack_t **stack, int size) {
    stack_t *s;
    s = malloc(sizeof(stack_t));
    if (!s) {
        printf("Memory allocation error\n");
        return -1;
    }
    s->size = 0;
    s->top = NULL;
    s->frameSize = size;
    *stack = s;
    return 0;
}

int 
destroyStack(stack_t **S) {
    frame_t *temp;

    if ((*S)->top == NULL) {
        printf("%s Empty Stack\n", __FUNCTION__);
        return 0;
    }
    
    if ((*S)->size) { 
        printf("W A R N I N G!!! Deleting nonEmpty stack\n");    
    }

    frame_t *cur = (*S)->top;

    while (cur) {
        temp = cur;
        cur = cur->nxt;
        free(temp->pData);
        free(temp);
    } 

    free(*S);
    S = NULL;
    return 0;
}

int
push(stack_t *S, char *pData) 
{
    frame_t *pFrame = NULL;

    pFrame = malloc(sizeof(frame_t)); 

    if (!pFrame)
        return -1;

    pFrame->pData = malloc(S->frameSize);

    if (!pFrame->pData)
        return -1;

    memcpy(pFrame->pData, pData, S->frameSize);

    pFrame->nxt = S->top;
    S->top = pFrame;
    S->size++;

    return 0;
}

int 
pop(stack_t *S, char *rv) 
{
    frame_t *temp;
 char C;
    if (S->top == NULL) {
#ifdef DEBUG
        printf("%s : W A R N I G !!!  Pop from empty stack\n", __func__);
#endif        
        return 0;
    }
    temp = S->top;
    S->top = temp->nxt;     
    S->size--;
    rv = memcpy(rv, temp->pData, S->frameSize);

    free(temp);

    return 1;
}

void 
print(stack_t *S)
{
    frame_t *tFramePtr;
    long n;

    printf("\n");
    if (S == NULL) {
        printf("%s : Error, no Stack\n", __func__);
        return;
    }

    if (S->top == NULL) {
        printf("%s : Error, Empty stack\n", __func__);
        return;
    }

    tFramePtr = S->top;
    do {
        memcpy(&n, (tFramePtr->pData), S->frameSize);
        printf("\t%ld\n", n);
        tFramePtr = tFramePtr->nxt;
    } while(tFramePtr);

    printf("done\n");
    return;
}

void
getStackCount (stack_t *S) 
{ 
    printf("%d\n", S->size); 
}

#if TEST_STACK
int 
main(void) 
{
    stack_t *S;
    float n;
    createStack(&S, sizeof(n));     

    n = 1;
    push(S, &n);
    n = 21;
    push(S, &n);
    n = 121;
    push(S, &n);
    n = 31;
    push(S, &n);
    print(S);
    getStackCount(S);
    pop(S, &n);

    getStackCount(S);
    print(S);
    pop(S, &n);

    getStackCount(S);
    print(S);
    pop(S, &n);

    getStackCount(S);
    print(S);
    pop(S, &n);

    getStackCount(S);
    print(S);
    print(S);

    destroyStack(&S);
    print(S);
    destroyStack(&S);

    return 0;
}
#endif
