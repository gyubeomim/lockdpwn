/*
 * c ==> 해킹맛보기, 어셈블리용 cdecl 함수호출 코드 
 */
#include <stdio.h>

int __cdecl sum(int a,int b,int c)
{
	return a+b+c;
}

int main(int argc, const char *argv[])
{
	int s;
	s = sum(1,2,3);
	printf("%d\n",s);

	return 0;
}

