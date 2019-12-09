/*
  c ftz ==> strcpy 함수의 버퍼오버플로우를 실행하기 위한 코드
 */
#include <stdio.h>
#include <string.h>

void test(char *bad)
{
	char buffer[16];
	strcpy(buffer, bad);
}

void main(int argc, char *argv[])
{
	printf("hello");
	test(argv[1]);
}

















