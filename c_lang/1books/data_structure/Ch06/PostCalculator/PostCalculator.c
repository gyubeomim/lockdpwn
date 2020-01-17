#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"

int EvalRPNExp(char exp[])
{
	Stack stack;
	int expLen = strlen(exp);
	int i;
	char tok, op1, op2;

	StackInit(&stack);

	for(i=0; i<expLen; i++)
	{
		tok = exp[i];

		if(isdigit(tok))
		{
			SPush(&stack, tok - '0');     // 숫자로 변환하여 PUSH!
		}
		else
		{
			op2 = SPop(&stack);     // 먼저 꺼낸 값이 두 번째 피연산자!
			op1 = SPop(&stack);

			switch(tok)
			{
			case '+':
				SPush(&stack, op1+op2);
				break;
			case '-':
				SPush(&stack, op1-op2);
				break;
			case '*':
				SPush(&stack, op1*op2);
				break;
			case '/':
				SPush(&stack, op1/op2);
				break;
			}
		}
	}
	return SPop(&stack);
}
