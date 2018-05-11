#include <stdio.h>

typedef struct _empInfo
{
	int empNum;    // 직원의 고유번호
	int age;     // 직원의 나이
}EmpInfo;

int main(void)
{
	EmpInfo empInfoArr[1000];
	EmpInfo ei;
	int eNum;

	printf("사번과 나이 입력: ");
	scanf("%d %d", &(ei.empNum), &(ei.age));
	empInfoArr[ei.empNum] = ei;    // 단번에 저장!

	printf("확인하고픈 직원의 사번 입력: ");
	scanf("%d", &eNum);

	ei = empInfoArr[eNum];    // 단번에 탐색!
	printf("사번 %d, 나이 %d \n", ei.empNum, ei.age);
	return 0;
}