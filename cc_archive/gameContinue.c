/*
  Name : gameContinue.c ver 1.0
  Content : 게임 저장, 이어하기
  Implementation : LKB
  Last modified 2016/07/08
*/


#include "common.h"
#include "game.h"
#include "gameTimes.h"
#include "gameMoney.h"


void saveCurrentState(int moneyCom, int moneyYou,int win,int lose,int draw,int moneyAmount)
{
  FILE *fp = fopen("game.dat","w");

  fprintf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n",moneyCom,moneyYou,win,lose,draw,moneyAmount);

  printf("\n[*] 현재 상태를 저장했습니다\n\n");
  
}


int loadSavedFile()
{

  int moneyC = 0, moneyY = 0;
  int win,lose,draw,moneyAmount;
  FILE *fp = fopen("game.dat","r");

  if (fp == NULL)
  {
    return;
  }

  fscanf(fp,"%d\n%d\n%d\n%d\n%d\n%d\n%d",&moneyC,&moneyY,&win,&lose,&draw,&moneyAmount,&percent);

  setComMoney(moneyC);
  setYouMoney(moneyY);
  return win,lose,draw,moneyAmount;
}
