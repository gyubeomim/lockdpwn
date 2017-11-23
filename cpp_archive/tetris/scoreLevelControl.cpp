

#include "stdafx.h"
#include "keyCurControl.h"

#define LEVEL_DIFF 2				// 단계별 속도 증가 정보
#define LEVEL_UP_SCORE_DIFF 200    // 레벨이 증가하는 스코어 간격 정보

static int curGameLevel = 1;
static int curGameScore = 0;

void showCurrentScoreAndLevel()
{

	setCurrentCursorPos(30, 4);
	printf("& 현재 레벨 : %d  &", curGameLevel);

	setCurrentCursorPos(30, 7);
	printf("& 현재 점수 : %d  &", curGameScore);

}


void gameLevelUp()
{
	curGameLevel++;
	keyDelaySpeedCtl(LEVEL_DIFF);
}


void addGameScore(int score)
{
	if (score < 1)
		return;

	curGameScore += score;


	// 레벨 상승 확인 후 레벨 up!
	if (curGameScore >= curGameLevel * LEVEL_UP_SCORE_DIFF)
		gameLevelUp();

}

