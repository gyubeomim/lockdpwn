/*
  Name : game.h ver 1.0
  Content : 게임 관련 함수 선언
  Implementation : LKB
  Last modified 2016/07/07
*/


#ifndef __GAME_H__

#define __GAME_H__


enum{scissors=1,rock,paper,quit};


int choiceOfCom();
int choiceOfMe(int win,int lose,int draw,int moneyAmount);
int whoIsWinner(int com,int you);

#endif

/* end of line */
