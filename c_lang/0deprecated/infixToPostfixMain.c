/*
  자료구조 p237 중위표기법 -> 후위표기법으로 변환하는 main 함수  
*/

#include <stdio.h>
#include "infixToPostfix.h"

void main()
{
     char exp1[] = "1+2*3";
     char exp2[] = "(1+2)*3";
     char exp3[] = "((1-2)+3)*(5-2)";


     convToRPNExp(exp1);
     convToRPNExp(exp2);
     convToRPNExp(exp3);

     printf("%s \n",exp1);
     printf("%s \n",exp2);
     printf("%s \n",exp3);
     
}
