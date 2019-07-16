#include "stdafx.h"
#include <conio.h>
#include <Windows.h>
#include "point.h"
#include "blockStageControl.h"

#define KEY_SENSITIVE 100
#define SYS_DELAY 20

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define SPACE 32  // 스페이스바 처리를 위한 매크로


static int keyDelayRate;



// 깜빡거리는 커서를 제거한다 
void removeCursor()
{
  CONSOLE_CURSOR_INFO curInfo;

  GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
  curInfo.bVisible = 0;

  SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}

// 현재 커서의 위치정보를 담은 구조체 변수를 반환한다
POINT_EDWARD getCurrentCursorPos()
{
  POINT_EDWARD curPoint;
  CONSOLE_SCREEN_BUFFER_INFO curInfo;

  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);

  curPoint.x = curInfo.dwCursorPosition.X;
  curPoint.y = curInfo.dwCursorPosition.Y;

  return curPoint;

}

// 커서의 위치를 설정한다
void setCurrentCursorPos(int x, int y)
{
  COORD pos = { x, y };
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

}

// 키 입력 처리 함수
// 핵심!
int insertUserKeyInput()
{
  int key;

  for (int i = 0; i < KEY_SENSITIVE; i++)
  {
    if (_kbhit() != 0)
    {
      key = _getch();

      switch(key)
      {
        case LEFT:
          shiftLeft();
          break;
        case RIGHT:
          shiftRight();
          break;
        case UP:
          rotateBlock();
          break;
        case SPACE:
          solidCurrentBlock();
          return 1;					// 스페이스바가 입력된 걸 알리기 위해
      }
    }
    if (i % keyDelayRate == 0)
    {
      Sleep(SYS_DELAY);
    }
  }

  return 0;
}


// 게임 속도를 증가시키는 함수
void keyDelaySpeedCtl(int addSpeed)
{
  keyDelayRate += addSpeed;
}


void initKeyDelayRate(int rate)
{
  if (rate < 1)
  {
    return;
  }

  keyDelayRate = rate;
}


/* end of file */
