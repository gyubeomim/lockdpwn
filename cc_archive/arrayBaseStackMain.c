#include <stdio.h>
#include "arrayBaseStack.h"


void main()
{
     Stack stack;
     stackInit(&stack);


     sPush(&stack,1); sPush(&stack,2);
     sPush(&stack,3); sPush(&stack,4);
     sPush(&stack,5); 
     
     while(!sIsEmpty(&stack))
     {
          printf("%d ",sPop(&stack));
     }

     printf("\n\n");
}
