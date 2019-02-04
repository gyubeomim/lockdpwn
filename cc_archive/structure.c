/*
 * c ==> 해킹맛보기, 어셈블리용 구조체 코드 
 */
#include <stdio.h>

struct ST
{
	int sv_1;
	int sv_2;
	int sv_3;
};

int main(int argc, const char *argv[])
{
	struct ST st;
	st.sv_1 = 1;
	st.sv_2 = 2;
	st.sv_3 = 3;
	
	printf("%x, %x, %x\n", st.sv_1, st.sv_2, st.sv_3);

	return 0;
}

