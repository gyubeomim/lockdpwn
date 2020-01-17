/*
  c 자동제어 ==> 2차 지연 시스템을 재현한 코드 (RLC 회로, 질량댐퍼스프링시스템)
*/
#include "stdafx.h"
#include <conio.h>
#include <string.h>
#include <Windows.h>

float w[2000];
float omega = 10, delta = 1, rr = 1.0;

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

  printf("1차 지연시스템의 출력을 저장\n");
  printf("저장할 파일의 이름을 입력하세요\n");
  printf("파일이름 :");

  scanf("%s", fname);
  strcat(fname, ".dat");
  fp = fopen(fname, "w");

  printf("### 데이터 저장중...\n");
  for (i = 0; i < 2000; i++)
  {
    fprintf(fp, "%f	%f\n", i*0.001, w[i]);
  }
  fclose(fp);
  printf("### 데이터 저장이 완료됐습니다\n");

}

void para_input()
{
  clrscr();

  gotoxy(10, 5);
  printf("2차 지연 시스템의 각 파라미터를 입력하세요");

  gotoxy(10, 8);
  printf("목표입력 R = [%f] ", rr);
  scanf("%f", &rr);

  gotoxy(10, 10);
  printf("각주파수 wn [rad/sec] = [%f] ", omega);
  scanf("%f", &omega);

  gotoxy(10, 12);
  printf("감쇠계수 delta = [%f] ", delta);
  scanf("%f", &delta);

}

void main()
{
  unsigned int i;
  float error,ee, ee1, gg, gg1, gg2, ww;

  para_input();

  i = 0;
  ee = .0;	// 전압오차
  ee1 = .0;
  gg = .0;
  ww = .0;	// 각속도
  error = .0;
  gg1 = .0;
  gg2 = .0;

  w[0] = 0;

  /*
    delta		// 감쇠계수
    omega		// 각주파수 Wn
    ei			// 입력전압 (V)
    gg			// 시정수의 역수 (1/T)
  */

  while (i < 2000)
  {
    error = rr - gg2;
    ee = omega * omega * error;			// 전압오차 계산
    ww += (ee + ee1)*0.001 / 2;			// 적분 후 각속도로 대입한다 (주기시간 0.001초)

    gg = ww - 2 * delta * omega * gg2;
    gg2 += (gg + gg1)*0.001 / 2;

    w[i] = gg2;

    //printf("출력값 w[%d] = %f \n", i, w[i]);

    ee1 = ee;
    gg1 = gg;
    i++;
  }

  save();
}
