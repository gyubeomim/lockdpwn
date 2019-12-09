/*
 * c ==> 해킹맛보기, 어셈블리용 switch문 코드 
 */
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int lv = 2;

	switch(lv)
	{
		case 0:
			printf("lv is 0\n");
			break;
		case 1:
			printf("lv is 1\n");
			break;
		case 2:
			printf("lv is 2\n");
			break;
	}

	return 0;
}

