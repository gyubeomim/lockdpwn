/*
	c 자동제어 ==> 폐루프에서 모터의 입력전압에 따른 각속도 비교하는 코드
*/
#include "stdafx.h"
#include <math.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

float w[1000];
float current[1000];
float ri = 5.0, kt = 0.5, jj = 0.101, kv = 0.68, tl =0.0;
float rr = 5.0, kp = 3.0, ki = 2.0, kd = 0.0;

/// vc++에선 gotoxy()와 clrscr()함수를 지원하지 않는다
void gotoxy(int x, int y)
{
	COORD Pos = { x,y };

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void clrscr()
{
	system("cls");
}

void save()
{
	FILE *fp;
	char fname[20];
	int i;

	printf("전동기의 상태를 저장\n");
	printf("저장할 파일의 이름을 입력하세요\n");
	printf("파일이름 :");

	scanf("%s", fname);
	strcat(fname, ".dat");
	fp = fopen(fname, "w");

	printf("### 데이터 저장중...\n");
	for (i = 0; i < 1000; i++)
	{
		fprintf(fp, "%f	%f	%f\n", i*0.01, current[i], w[i]);
	}
	fclose(fp);
	printf("### 데이터 저장이 완료됐습니다\n");

}

void para_input()
{
	clrscr();
	
	gotoxy(10, 4);
	printf("직류 전동기의 회전 속도 제어");
	gotoxy(10, 5);
	printf("직류 전동기의 각 파라미터를 입력하세요");

	gotoxy(10, 10);
	printf("모터의 저항[ohm] = [%f] ", ri);
	scanf("%f", &ri);

	gotoxy(10, 12);
	printf("모터의 전류/토크 계수[Nm/A] = [%f] ", kt);
	scanf("%f", &kt);

	gotoxy(10, 14);
	printf("관성 모멘트[] = [%f] ", jj);
	scanf("%f", &jj);

	gotoxy(10, 16);
	printf("역기전력 상수[V/rads/s] = [%f] ", kv);
	scanf("%f", &kv);

	gotoxy(10, 18);
	printf("외란 = [%f] ", tl);
	scanf("%f", &tl);

	gotoxy(10, 20);
	printf("직류 전동기의 제어기 이득값을 입력하시오");
	
	gotoxy(10, 21);
	printf("목표 회전속도[rad/s] = [%f] ", rr);
	scanf("%f", &rr);

	gotoxy(10, 22);
	printf("비례 이득값 [v/rad/s] = [%f] ", kp);
	scanf("%f", &kp);

	gotoxy(10, 23);
	printf("적분 이득값[] = [%f] ", ki);
	scanf("%f", &ki);

	gotoxy(10, 24);
	printf("미분 이득값[] = [%f] ", kd);
	scanf("%f", &kd);

}

void main()
{
	unsigned int i;
	float ei, ee, ii, tt, tj, ww, tj1;
	float error, error1, error2;

	i = 0;
	ei = 0.0;	// 입력전압 
	ee = 0.0;	// 전압오차
	ii = 0.0;	// 전류
	tt = 0.0;	// 구동토크
	tj = 0.0;	// 필요토크 (Tj)
	ww = 0.0;	// 각속도
	tj1 = 0.0;	// 이전필요토크 (이전 tj값)
	w[0] = 0;
	current[0] = 0.0;	//

	error = .0;
	error1 = .0;
	error2 = .0;
	
	/*
		ei			// 입력전압 (V)
		ri			// 모터의 저항 (Ohm)
		kt			// 모터의 전류/토크 계수 (Kt)(Nm/A)
		jj			// 관성모멘트
		kv			// 유기전압정수 (..?)
		rr			// 목표 회전속도
		kp			// 비례이득
		ki			// 적분이득
		kd			// 미분이득
	*/

	para_input();

	while (i < 1000)
	{
		error = rr - ww;											// 오차계산
		error2 += (error + error1)*0.01 / 2;						// 적분
		ei = kp*error + error2*ki + kd *(error - error1) / 0.01;	// PID제어기

		ee = ei - kv*ww;			// 전압오차 계산 ( V = V0 - Kv*w )
		ii = ee / ri;				// 전류 계산 ( I = V/R )
		tt = kt *ii;				// 모터의 구동 토크 계산 ( T = Kt * I )
		tj = (tt - tl) / jj;		// 모터축의 필요 회전 토크 계산 ( Tj = (T - Tl) / J )
		ww += (tj + tj1)*0.01 / 2;	// 적분 후 각속도로 대입한다 (주기시간 0.01초)
		
		w[i] = ww;
		current[i] = ii;

		error1 = error;

		printf("error = %f     ei = %f     ee =%f	  tt = %f     tj = %f	  w[%d] = %f\n"
			, error, ei, ee, tt, tj, i, w[i]);

		tj1 = tj;
		i++;
	}

//	save();
}

