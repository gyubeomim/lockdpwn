// tetris.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <Windows.h>

void main()
{
  COORD pos1 = { 0, 2 };
  COORD pos2 = { 6, 6 };
  COORD pos3 = { 15,4 };

  HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	
  SetConsoleCursorPosition(hConsoleOut, pos1);
  printf("첫번째 인사 : 안녕하세용");
  getchar();


  SetConsoleCursorPosition(hConsoleOut, pos2);
  printf("두번째 인사 : 안녕하세용");
  getchar();


  SetConsoleCursorPosition(hConsoleOut, pos3);
  printf("세번째 인사 : 안녕하세용");
  getchar();


}
