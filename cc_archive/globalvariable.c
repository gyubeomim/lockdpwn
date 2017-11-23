/*
 * c ==> 해킹맛보기, 어셈블리용 전역변수 코드 
 */
#include <stdio.h>

int gv;

int main(int argc, const char *argv[])
{
	gv = 2;
	printf("%x\n",gv);

	return 0;
}

