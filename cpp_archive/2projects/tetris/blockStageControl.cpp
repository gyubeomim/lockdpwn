/*
  Name : blockStageControl.cpp ver 1.0
  Content :
  Implementation : LKB

  Last modified 2016/07/12
*/

#include "stdafx.h"
#include "point.h"
#include "blockInfo.h"
#include "keyCurControl.h"
#include "scoreLevelControl.h"
#include <time.h>
#include <Windows.h>

#define GBOARD_WIDTH 10
#define GBOARD_HEIGHT 20

#define GBOARD_ORIGIN_X 4
#define GBOARD_ORIGIN_Y 2


static int gameBoardInfo[GBOARD_HEIGHT + 1][GBOARD_WIDTH + 2] = { 0, };

static int currentBlockModel;
static int curPosX, curPosY;
static int rotateSte;


void initNewBlockPos(int x, int y)
{
  if (x < 0 || y < 0)
    return;

  curPosX = x;
  curPosY = y;

  setCurrentCursorPos(x, y);
}


void chooseBlock()
{
  srand((unsigned int)time(NULL));

  currentBlockModel = (rand() % NUM_OF_BLOCK_MODEL) * 4;

}



// 현재 출력해야하는 블록의 index 정보를 반환한다
int getCurrentBlockIdx()
{
  return currentBlockModel + rotateSte;
}



void showBlock(char blockInfo[][4])
{
  int y, x;

  POINT_EDWARD curPos = getCurrentCursorPos();

  for (y = 0; y < 4; y++)
  {
    for (x = 0; x < 4; x++)
    {
      setCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

      if (blockInfo[y][x] == 1)
        printf("■");
    }
  }

  setCurrentCursorPos(curPos.x, curPos.y); // 커서 위치 원래대로 한다
}



void deleteBlock(char blockInfo[][4])
{
  POINT_EDWARD curPos = getCurrentCursorPos();

  for (int y = 0; y < 4; y++)
  {
    for (int x = 0; x < 4; x++)
    {
      setCurrentCursorPos(curPos.x + (x * 2), curPos.y + y);

      if (blockInfo[y][x] == 1)
        printf("  "); // 공백 두 칸
    }
  }

  setCurrentCursorPos(curPos.x, curPos.y);
}

// gameBoardInfo에 현재 정보를 추가하는 함수
void addCurrentBlockInfoToBoard()
{
  int x, y;

  int arrCurX;
  int arrCurY;

  for (y = 0; y < 4; y++)
  {
    for (x = 0; x < 4; x++)
    {
      arrCurX = (curPosX - GBOARD_ORIGIN_X) / 2;
      arrCurY = curPosY - GBOARD_ORIGIN_Y;

      if (blockModel[getCurrentBlockIdx()][y][x] == 1)
      {
        gameBoardInfo[arrCurY + y][arrCurX + x] = 1;
      }
    }
  }

}



// 게임판에 굳어진 블록을 그린다
void drawSolidBlocks()
{
  int x, y;
  int cursX, cursY;

  for (y = 0; y < GBOARD_HEIGHT; y++)
  {
    for (x = 1; x < GBOARD_WIDTH + 1; x++)
    {
      cursX = x * 2 + GBOARD_ORIGIN_X;
      cursY = y + GBOARD_ORIGIN_Y;

      setCurrentCursorPos(cursX, cursY);

      if (gameBoardInfo[y][x] == 1)
        printf("■");
      else
        printf("  ");
    }
  }
}



// 행 단위로 채워진 블록을 삭제하는 함수
void removeFilledUpLine()
{
  int x, y;
  int line;


  for (y = GBOARD_HEIGHT - 1; y > 0; y--)
  {
    for (x = 1; x < GBOARD_WIDTH + 1; x++)
    {
      if (gameBoardInfo[y][x] != 1)
        break;
    }

    if (x == (GBOARD_WIDTH + 1))
    {
      for (line = 0; y - line > 0; line++)
      {
        memcpy(
            &gameBoardInfo[y - line][1],
            &gameBoardInfo[(y - line) - 1][1],
            GBOARD_WIDTH * sizeof(int)
               );
      }

      y++;	// 배열 정보가 아래로 한 칸씩 이동했으므로 증가시켜 원상복구시킨다.
      addGameScore(10);
      showCurrentScoreAndLevel();
    }
  }

  drawSolidBlocks();

}





// 블록의 충돌을 감지하는 함수
int detectCollision(int posX, int posY, char blockModel[][4])
{

  /* gameBoardInfo 배열의 좌표로 변경 */
  int arrX = (posX - GBOARD_ORIGIN_X) / 2;
  int arrY = posY - GBOARD_ORIGIN_Y;

  for (int x = 0; x < 4; x++)
  {
    for (int y = 0; y < 4; y++)
    {
      if (blockModel[y][x] == 1 && gameBoardInfo[arrY + y][arrX + x] == 1)
        return 0;
    }
  }

  return 1;
}



// 블락이 하강한다
// 충돌검사 알고리즘 추가 후 이 파일은 변경된다 
int blockDown()
{
  // 바로 아래있는 칸하고 부딪히면
  if (!detectCollision(curPosX, curPosY + 1, blockModel[getCurrentBlockIdx()]))
  {
    addCurrentBlockInfoToBoard();
    removeFilledUpLine();
    return 0;
  }

  deleteBlock(blockModel[getCurrentBlockIdx()]);
  curPosY += 1;


  setCurrentCursorPos(curPosX, curPosY);
  showBlock(blockModel[getCurrentBlockIdx()]);
  return 1;

}




// 왼쪽으로 이동한다
void shiftLeft()
{
  // 충돌방지 추가 코드
  if (!detectCollision(curPosX -2, curPosY, blockModel[getCurrentBlockIdx()]))
    return;

  deleteBlock(blockModel[getCurrentBlockIdx()]);

  curPosX -= 2;

  setCurrentCursorPos(curPosX, curPosY);
  showBlock(blockModel[getCurrentBlockIdx()]);

}

// 오른쪽으로 이동한다
void shiftRight()
{
  // 충돌방지 추가 코드
  if (!detectCollision(curPosX+2, curPosY, blockModel[getCurrentBlockIdx()]))
    return;

  deleteBlock(blockModel[getCurrentBlockIdx()]);

  curPosX += 2;

  setCurrentCursorPos(curPosX, curPosY);
  showBlock(blockModel[getCurrentBlockIdx()]);

}

// 블록을 90도 회전시킨다
void rotateBlock()
{
  int nextRotSte;
  int beforeRotSte = rotateSte;

  deleteBlock(blockModel[getCurrentBlockIdx()]);

  nextRotSte = rotateSte + 1;
  nextRotSte %= 4;
  rotateSte = nextRotSte;

  // 충돌방지 추가 코드
  if (!detectCollision(curPosX, curPosY, blockModel[getCurrentBlockIdx()]))
  {
    rotateSte = beforeRotSte;
    return;
  }


  setCurrentCursorPos(curPosX, curPosY);
  showBlock(blockModel[getCurrentBlockIdx()]);
	
}

void drawGameBoard()
{
  int x, y;


  /* 시각적인 부분 처리 */
  for (y = 0; y <= GBOARD_HEIGHT; y++)
  {
    setCurrentCursorPos(GBOARD_ORIGIN_X, GBOARD_ORIGIN_Y + y);


    if (y == GBOARD_HEIGHT)
      printf("┗");
    else
      printf("┃");

  }


  for (y = 0; y <= GBOARD_HEIGHT; y++)
  {
    setCurrentCursorPos(
        GBOARD_ORIGIN_X + (GBOARD_WIDTH + 1) * 2,
        GBOARD_ORIGIN_Y + y);

    if (y == GBOARD_HEIGHT)
      printf("┛");
    else
      printf("┃");


  }

  for (x = 1; x < GBOARD_WIDTH + 1; x++)
  {
    setCurrentCursorPos(
        GBOARD_ORIGIN_X + x * 2, GBOARD_ORIGIN_Y + GBOARD_HEIGHT);

    printf("━");

  }
  setCurrentCursorPos(0, 0);


  /* 데이터 부분 처리 */
  for (int y = 0; y < GBOARD_HEIGHT; y++)
  {
    gameBoardInfo[y][0] = 1;
    gameBoardInfo[y][GBOARD_WIDTH + 1] = 1;
  }

  for (int x = 0; x < GBOARD_WIDTH + 2; x++)
  {
    gameBoardInfo[GBOARD_HEIGHT][x] = 1;
  }


}




// 게임 종료 함수
int isGameOver()
{
  // 처음 블록이 등장할 때 충돌이 감지되면 게임 패배
  if (!detectCollision(curPosX, curPosY, blockModel[getCurrentBlockIdx()]))
  {
    return 1;
  }
  else
    return 0;
}








// 현재 블락을 바닥으로 이동시켜 굳힌다
void solidCurrentBlock()
{
  while (blockDown());
}









// 스페이스바를 누르면 바로 내려가는 함수

/*
  void goDirectlyWithSpace()
  {
  int i = 0;

  deleteBlock(blockModel[getCurrentBlockIdx()]);


  // 부딪히기 전까지 i 값을 계속 증가시키고
  while (!detectCollision(curPosX, curPosY + i, blockModel[getCurrentBlockIdx()]))
  {
  i++;
  }

  // 그 i 값을 더한다
  curPosY += i;

  setCurrentCursorPos(curPosX, curPosY);
  showBlock(blockModel[getCurrentBlockIdx()]);

  }
*/


// 한 줄이 꽉찼는지 확인하는 함수
/*
  void oneLineIsFilled()
  {
  int count = 0;


  for (int x = 1; x < GBOARD_WIDTH + 1; x++)
  {

  if (gameBoardInfo[GBOARD_HEIGHT - 1][x] == 1)
  {
  count++;
  }

  }


  // 10개 모두 꽉 차있으면
  if (count == 10)
  {
  // 한 줄을 지우고
  deleteLastLine();

  // 윗쪽 줄 정보를 아래로 내린다
  for (int y = 0; y < GBOARD_HEIGHT; y++)
  {
  for (int x = 0; x < GBOARD_WIDTH; x++)
  {
  gameBoardInfo[y][x] = gameBoardInfo[y - 1][x];
  }
  }
  }
  }
*/


/* end of file */
