#include <stdio.h>
#include <stdlib.h>
#include "arrayBaseStack.h"

void stackInit(Stack *pstack)
{
     pstack->topIndex = -1;
}


int sIsEmpty(Stack *pstack)
{
     if(pstack->topIndex == -1)
     {
          return TRUE;
     }
     else
          return FALSE;
}


void sPush(Stack *pstack, Data data)
{
     pstack->topIndex += 1;
     pstack->stackArr[pstack->topIndex] = data;

}


Data sPop(Stack *pstack)
{
     int rIdx;

     if(sIsEmpty(pstack))
     {
          printf("Stack Memory Error!");
          exit(-1);
     }

     rIdx = pstack->topIndex;
     pstack->topIndex -= 1;

     return pstack->stackArr[rIdx];
}



Data sPeek(Stack *pstack)
{
     if(sIsEmpty(pstack))
     {
          printf("Stack Memory Error!");
          exit(-1);
     }

     return pstack->stackArr[pstack->topIndex];
}
