/*
	c 자동제어 ==> 개루프에서 모터의 입력전압에 따른 각속도 비교하는 코드
*/
#include "stdafx.h"
#include <math.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

float w[1000];
float current[1000];
float ei = 5.0, ri = 5.0, kt = 0.5, jj = 0.101, kv = 0.68;

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

	gotoxy(10, 5);
	printf("직류 전동기의 각 파라미터를 입력하시오");
	gotoxy(10, 8);
	printf("입력 전압[V] = [%f] ", ei);
	scanf("%f", &ei);

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
	printf("유기전압정수[V/rad/s] = [%f] ", kv);
	scanf("%f", &kv);
}

void main()
{
	unsigned int i;
	float ee, ii, tt, tl, tj, ww, tj1;

	i = 0;		
	tl = 0.0;	// 외란 (Tl) : 내가 원하는 값으로 설정할 수 있다 , 0.2
	ee = 0.0;	// 전압오차
	ii = 0.0;	// 전류
	tt = 0.0;	// 구동토크
	tj = 0.0;	// 필요토크 (Tj)
	ww = 0.0;	// 각속도
	tj1 = 0.0;	// 이전필요토크 (이전 tj값)
	current[0] = 0.0;	//

	/*
		ei			// 입력전압 (V)
		ri			// 모터의 저항 (Ohm)
		kt			// 모터의 전류/토크 계수 (Kt)(Nm/A)
		jj			// 관성모멘트
		kv			// 유기전압정수..?
	*/

	para_input();

	while (i < 1000)
	{
		ee = ei - kv*ww;	// 전압오차 계산 ( V = V0 - Kv*w )
		ii = ee / ri;		// 전류 계산 ( I = V/R )
		tt = kt *ii;		// 모터의 구동 토크 계산 ( T = Kt * I )
		tj = (tt - tl) / jj;	// 모터축의 필요 회전 토크 계산 ( Tj = (T - Tl) / J
		ww += (tj + tj1) * 0.01 / 2;	// 적분 후 각속도로 대입한다 (주기시간 0.01초)

		w[i] = ww;	
		current[i] = ii;

		printf(" 구동토크[tt] = %f, 회전토크[tj] = %f, 각속도[ww] = %f, 전압오차[ee] = %f, 최종각속도[w[%d]] = %f \n"
			, tt, tj, ww, ee, i, w[i]);
		tj1 = tj;
		i++;
	}

//	save();
}

