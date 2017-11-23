/*
	c 자동제어 ==> x^2 + 3*x + 6 함수를 후퇴차분법으로 적분, 미분하는 예제 코드
*/
#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUM 5000

int data_in(int *n, float *a, float *b);
float chabun(int n, float a, float b, float *s, float *y);
int solution_out(int n, float a, float b, float s,float y);
float func(float x);
int save(int n, float a, float b);

float mibun[MAX_NUM];
float jukbun[MAX_NUM];
float function[MAX_NUM];

int main()
{
	int n;
	float a, b, s, y;

	while (1)
	{
		data_in(&n, &a, &b);
		chabun(n, a, b, &s, &y);
		solution_out(n, a, b, s, y);
	}
	/// save(n, a, b);   /// 우선 저장할 일 없다

	return 0;
}

int data_in(int *n, float *a, float *b)
{
	printf("\n -------------------------\n");
	printf("차분적분영역 [a,b] \n");
	printf("a[시간] = ");
	scanf("%f", &*a);
	printf("b[시간] = ");
	scanf("%f", &*b);
	printf("분할수[n] = ");
	scanf("%d", &*n);

	return 0;
}

float func(float x)
{
	float fx;

	/// 이 함수에 대한 후퇴차분법을 사용해 적분하는듯 ㅇㅇ
	fx = x*x + 3 * x + 6;

	return fx;
}


float chabun(int n, float a, float b, float *s, float *y)
{
	float f1, f2, h, x;
	int i = 0;
	h = (b - a) / n;
	x = a;
	f1 = 0;
	f2 = 0;

	*y = 0.0;
	*s = 0.0;
	mibun[0] = 0;
	jukbun[0] = 0;
	function[0] = 0;

	/// 미분 먼저하고
	do{
		f1 = func(x);
		*y = (f1 - f2) / h;
		x = x + h;
		f2 = f1;
		mibun[i] = *y;
		function[i] = f1;
		i++;
	} while (x < b);


	h = (b - a) / n;
	x = a;
	f1 = 0;
	f2 = 0;
	/// 적분을 수행한다
	for (i = 0; i < MAX_NUM; i++)
	{
		f1 = func(x);
		*s = *s + f1 * h + (f1 - f2)*h / 2;
		x = x + h;
		f2 = f1;
		jukbun[i] = *s;
		function[i] = f1;
	}

	return *s;
}

int solution_out(int n, float a, float b, float s, float y)
{
	printf("\n");
	printf("차분적분법 \n \n");
	printf("적분[미분]영역 \n \n");
	printf("하한경계 : %f \n", a);
	printf("상한경계 : %f \n", b);
	printf("분할수 : %d \n \n", n);
	printf("*** 해 *** \n");
	printf("적분 s = %e \n", s);
	printf("미분 y = %e \n", y);

	return 0;
}

int save(int n, float a, float b)
{
	FILE *fp;

	char fname[20];
	int i;
	float h;
	h = (b - a) / n;
	printf("계산한 데이터 값 저장 \n");
	printf("저장할 파일 이름을 입력하세요 \n");
	printf("파일이름 : ");
	scanf_s("%s", fname, 100);
	strcat(fname, ".dat");

	fopen_s(&fp, fname, "w");

	printf("[+] 데이터 저장 중...");
	for (i = 0; i < 2000; i++)
	{
		fprintf(fp, "%f    %f    %f \n", i*h, function[i], jukbun[i]);
	}
	fclose(fp);
	printf("[*}데이터를 저장 완료했습니다");

	return 0;
}