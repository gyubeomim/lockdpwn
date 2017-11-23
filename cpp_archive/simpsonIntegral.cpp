/*
	c 자동제어 ==> x^2 + 3*x + 6 함수를 simpson법으로 적분하는 예제 코드
*/
#include "stdafx.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUM 5000

int data_in(int *n, float *a, float *b);
float simpson(int n, float a, float b, float *s);
int solution_out(int n, float a, float b, float s);
float func(float x);
int save(int n, float a, float b);

float jukbun[MAX_NUM];
float function[MAX_NUM];

int main()
{
	int n;
	float a, b, s;

	while (1)
	{
		data_in(&n, &a, &b);
		simpson(n, a, b, &s);
		solution_out(n, a, b, s);
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

int solution_out(int n, float a, float b, float s)
{
	printf("\n");
	printf("심프슨법 \n \n");
	printf("적분영역 \n \n");
	printf("하한경계 : %f \n", a);
	printf("상한경계 : %f \n", b);
	printf("분할수 : %d \n \n", n);
	printf("*** 해 *** \n");
	printf("s = %e \n", s);

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

float simpson(int n, float a, float b, float *s)
{
	float f1, f2, f3, h, sw, x;
	h = (b - a) / n;
	x = a;
	*s = 0.0;

	do {
		f1 = func(x);
		f2 = func(x + h);
		f3 = func(x + 2.0 * h);
		sw = f1 + 4.0 * f2 + f3;
		*s += sw;
		x = x + 2.0 * h;
	} while (x < b);

	*s = *s * h / 3.0;
	return *s;
}