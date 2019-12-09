/*
  Name : gameMoney.c ver 1.0
  Content : 게임 머니 관련 함수 정의
  Implementation : LKB
  Last modified 2016/07/08
*/

#include "common.h"
#include "game.h"

static int moneyCom;
static int moneyYou;


static int gamblingTableMoney;

void setComMoney(int money)
{
  if(money<0)
  {
    return;
  }
  moneyCom = money;
}


int getCurrentComMoney()
{
  return moneyCom;
}

void setYouMoney(int money)
{
  if(money<0)
  {
    return;
  }
  moneyYou = money;

}


int getCurrentYouMoney()
{
  return moneyYou;
}

void setGamblingTableMoney(int money)
{
  if(money<0)
  {
    gamblingTableMoney =0;
  }
  else
  {
    gamblingTableMoney =  money;
  }

}

void comWinMoneyAccount()
{
  moneyYou -= gamblingTableMoney;
  moneyCom += gamblingTableMoney;
}


void youWinMoneyAccount()
{
  moneyYou += gamblingTableMoney;
  moneyCom -= gamblingTableMoney;
}

/* end of file */
