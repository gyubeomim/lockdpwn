/*
	c 자동제어 ==> 최소제곱법을 통해 데이터 개수와 데이터 좌표를 받아 예측 직선을 그려주는 코드
*/
#include "stdafx.h"
#include <math.h>

#define m 200
#define m1 2

float x[m], y[m], est_pt;

int data_in(int *n);
float least_square(int n, float p1[], float dsd1[], float b[], float *cd, float *sd, float *dss, float *est_p1); 
int solution_out(int n, float p1[], float dsd1[], float b[], float *cd, float *sd, float *dss, float *est_p1);

int main()
{
	int n;
	float p1[m], dsd1[m], b[m];
	float cd, sd, dss, est_p1;

	/*
		n			데이터개수
		x[i],y[i]	데이터 좌표
		p1			P1의 값
		dsd1		잉여 ri
		b[0],b[1]	직선 ax + b의 계수 a,b
		cd			결정계수
		sd			표준편차
		dss			잉여 제곱합
		est_pt		추정점
		est_p1		추정치
	*/

	data_in(&n);
	est_p1 = least_square(n, p1, dsd1, b, &cd, &sd, &dss, &est_p1);
	solution_out(n, p1, dsd1, b, &cd, &sd, &dss, &est_p1);

}

int data_in(int *n)
{
	int i;

	printf("데이터 입력(최소자승법)\n");
	printf("x, y 좌표점 입력 갯수 : n = ");
	scanf("%d", *&n);

	printf("추정점 입력 est_pt = ");
	scanf("%f", &est_pt);

	printf("좌표 데이터 입력 x[i], y[i] = \n\n");
	
	for (i = 1; i <= *n; i++)
	{
		printf("x[%d] = ", i);
		scanf("%f", &x[i]);
		printf("y[%d] = ", i);
		scanf("%f", &y[i]);
	}

	return 0;
}

float least_square(int n, float p1[], float dsd1[]
	, float b[], float *cd, float *sd, float *dss, float *est_p1)
{
	int i;
	float xsum, ysum, xysum, x2, y2;

	xsum = 0;
	ysum = 0;
	xysum = 0;
	x2 = 0;
	y2 = 0;
	*dss = 0;

	for (i = 1; i <= n; i++)
	{
		xsum += x[i];
		ysum += y[i];
		xysum += x[i] * y[i];
		x2 += x[i] * x[i];
		y2 += y[i] * y[i];
	}

	b[0] = (n * xysum - xsum*ysum) / 
			(n*x2 - xsum * xsum);
	
	b[1] = (x2 * ysum - xsum*xysum) / 
			(n*x2 - xsum * xsum);

	for (i = 1; i <= n; i++)
	{
		p1[i] = b[0] * x[i] + b[1];
		dsd1[i] = y[i] - p1[i];
		*dss += dsd1[i] * dsd1[i];
	}

	*cd = sqrt(1 - *dss / (y2 - ysum*ysum / n));
	*sd = sqrt(*dss / (n - 2)); 
	*est_p1 = b[0] * est_pt + b[1];

	return *est_p1;
}

int solution_out(int n, float p1[], float dsd1[]
	, float b[], float *cd, float *sd, float *dss, float *est_p1)
{
	int i;

	printf("1차 다항식을 위한 최소자승법\n");
	printf("xy 좌표점의 개수 : %d \n",n);
	printf("근사방정식 \n");

	if (b[1] < 0)
	{
		b[1] = fabs(b[1]);
		printf("p1(x) = %f x - %f \n", b[0], b[1]);
	}
	else
	{
		printf("p1(x) = %f x + %f \n", b[0], b[1]);
	}

	printf("\n-----------------------------------------------------------------------------------\n");
	printf(" i		  x[i]		  y[i]	 	  p1[i]		  y[i] - p1[i]		  ");
	printf("\n-----------------------------------------------------------------------------------\n");

	for (i = 1; i <= n; i++)
	{
		printf("%2d	      %f	      %f	      %f	       %f \n", i, x[i], y[i], p1[i], dsd1[i]);
	}

	printf("y[i] - p1[i]의 제곱합 : %f \n", *dss);
	printf("결정계수 : %f \n", *cd);
	printf("표준편차 : %f \n", *sd);
	printf("\n 추정값 \n");
	printf("	x		p1	\n");
	printf("   %f       %f \n", est_pt, *est_p1);

	return 0;
		
}








