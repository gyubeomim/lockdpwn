/*
 * c ==> 해킹맛보기, 어셈블리용 for문 코드 
 */
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int lv;

	for(lv = 0; lv < 2; lv++)
	{
		printf("%x\n", lv);
	}

	return 0;
}

