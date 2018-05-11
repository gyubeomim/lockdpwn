#include "stdafx.h"
#include <Windows.h>
#include "keyCurControl.h"
#include "blockStageControl.h"
#include "scoreLevelControl.h"

#define START_CURPOS_X (5*2)
#define START_CURPOS_Y (0)

void main()
{
  // 게임 속도 설정
  initKeyDelayRate(10);
  // 커서 깜빡임 제거
  removeCursor();
  // 게임 보드 그리기
  drawGameBoard();
  showCurrentScoreAndLevel();

  while (1)
  {
    // 새 블록의 등장위치 설정
    initNewBlockPos(START_CURPOS_X, START_CURPOS_Y);
    // 블록 선택
    chooseBlock();

    if (isGameOver())
    {
      break;
    }
    while (1)
    {
      if (!blockDown())
      {
        // addCurrentBlockInfoToBoard();  // 호출 위치를 blockDown함수 안으로 옮겼다
        break;
      }
      if (insertUserKeyInput())
        break;
    }
  }
  setCurrentCursorPos(10, 10);
  puts("GAME OVER!\n");
}
/* end of file*/
