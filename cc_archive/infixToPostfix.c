/*
  열혈 자료구조 p236 Stack과 후위 표기법을 이용해 계산기 만들기
  후위표기법 알고리즘
 */

#include "ListBaseStack.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


// 각 연산자들의 우선순위 정하기
int getOpPrec(char op)
{
     switch(op)
     {
     case '*':
     case '/':
          return 5;
     case '+':
     case '-':
          return 3;
     case '(':
          return 1;
     }

     return -1;

          
}

// 우선순위를 통해 리턴값을 결정한다
int whoPrecOp(char op1,char op2)
{
     int op1Prec = getOpPrec(op1);
     int op2Prec = getOpPrec(op2);

     if(op1Prec > op2Prec)
     {
          return 1;
     }

     else if(op1Prec < op2Prec)
     {
          return -1;
     }

     else
     {
          return 0;
     }
          
}


// 중위 표기법을 (기존 계산기) 후위 표기법으로 변환하는 알고리즘
void convToRPNExp(char exp[])
{
     Stack *stack;

     int expLen = strlen(exp);
     char *convExp = (char*)malloc(expLen + 1);
     
     int i, idx= 0;
     char tok, popOp;
     
     memset(convExp, 0, sizeof(char)*expLen+1);
     StackInit(&stack);

     for(i=0; i<expLen;i++)
     {
          tok = exp[i];
          if(isdigit(tok))
          {
               convExp[idx++] = tok;
          }
          else
          {
               switch(tok)
               {
               case '(':
                    SPush(&stack,tok);
                    break;


               case ')':
                    while(1)
                    {
                         popOp = SPop(&stack);
                         if(popOp == '(')
                         {
                              break;
                         }
                         convExp[idx++] = popOp;
                    }
                    break;
               case '+': case '-':
               case '*': case '/':
                    // 연산기호들은 whoPrecOp를 이용해 우선순위에 따라 스택에 있는값을 빼오기도 하고 넣기도 한다
                    while(!SIsEmpty(&stack) && whoPrecOp(SPeek(&stack),tok) >= 0)
                         convExp[idx++] = SPop(&stack);

                    SPush(&stack,tok);
                    break;

                    
               }
          }
          
          
     }

 
     while(!SIsEmpty(&stack))
     {
          convExp[idx++] = SPop(&stack);
     }

     strcpy(exp,convExp);
     free(convExp);
     
}





