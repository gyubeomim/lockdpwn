



#include "stdafx.h"

#ifndef __BLOCKSTAGECONTROL_H__
#define __BLOCKSTAGECONTROL_H__


void initNewBlockPos(int x, int y);

void chooseBlock();

int getCurrentBlockIdx();
void showBlock(char blockInfo[][4]);
void deleteBlock(char blockInfo[][4]);

// 블록의 충돌을 감지하는 함수
int detectCollision(int posX, int posY, char blockModel[][4]);

int blockDown();
void shiftLeft();
void shiftRight();
void rotateBlock();

void drawGameBoard();

// gameBoardInfo에 현재 정보를 추가하는 함수
void addCurrentBlockInfoToBoard();

int isGameOver();

void drawSolidBlocks();
void removeFillUpLine();
void solidCurrentBlock();


#endif