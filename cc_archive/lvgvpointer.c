/*
 *  c ==> 해킹맛보기, 어셈블리용 지역,전역변수 + 포인터 코드
 */
#include <stdio.h>

int main(int argc, const char *argv[])
{
	int lv;
	int gv;

	lv = 1;
	gv = (int*)malloc(0x4);
	*gv = 2;

	printf("lv is %d\n", lv);
	printf("gv is %d\n", gv);

	return 0;
}
