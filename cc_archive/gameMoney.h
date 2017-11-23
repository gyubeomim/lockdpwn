/*
  Name : gameMoney.h ver 1.0
  Content : 게임 머니 관련 함수 정의
  Implementation : LKB
  Last modified 2016/07/06
*/

#ifndef __GAMEMONEY_H__
#define __GAMEMONEY_H__


void setComMoney(int money);
int getCurrentComMoney();

void setYouMoney(int money);
int getCurrentYouMoney();

void setGamblingTableMoney(int money);

void comWinMoneyAccount();
void youWinMoneyAccount();


#endif

/*  end of file */
