/*
  Name : gameContinue.h ver 1.0
  Content : 게임 저장,이어하기 선언 
  Implementation : LKB
  Last modified 2016/07/07
*/


#ifndef __GAMECONTINUE_H__
#define __GAMECONTINUE_H__


void saveCurrentState(int moneyCom, int moneyYou,int win,int lose,int draw, int moneyAmount);
int loadSavedFile();



#endif


/* end of file */
