#include <string.h>
#include <stdlib.h>
#include "InfixToPostfix.h"
#include "PostCalculator.h"

int EvalInfixExp(char exp[])
{
	int len = strlen(exp);
	int ret;
	char * expcpy = (char*)malloc(len+1);
	strcpy(expcpy, exp);

	ConvToRPNExp(expcpy);    
	ret = EvalRPNExp(expcpy);

	free(expcpy);
	return ret;
}
