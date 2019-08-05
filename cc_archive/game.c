/*
  Name : game.c ver 1.0
  Content : 게임 관련 함수 정의
  Implementation : LKB
  Last modified 2016/07/06
*/


#include <time.h>
#include "common.h"
#include "game.h"
#include "gameMoney.h"
#include "gameContinue.h"

int choiceOfCom()
{
  int rcp;
  srand((unsigned int)time(NULL));

  while(1)
  {
    //rcp는 1,2,3 중 임의의 한 숫자이다
    rcp = rand() %4;

    if(rcp != 0)
      break;
  }

  
  return rcp;
}



int choiceOfMe(int win,int lose,int draw,int moneyAmount)
{
  int myNum;
  int saveFlag = 0;

  while(1)
  {
    printf("\n가위(1), 바위(2), 보(3), 종료(4) 중 하나를 입력하세요:  ");
    scanf("%d",&myNum);

    if(myNum == 1 || myNum ==2 || myNum==3)
      break;
    else if(myNum ==4)
    {
      printf("\n[*]게임을 종료합니다\n\n");

      puts("게임을 저장하시겠습니까? < Yes : 1, No : 2 >: ");
      scanf("%d",&saveFlag);

      if(saveFlag == 1)
      {
        saveCurrentState(getCurrentComMoney(),getCurrentYouMoney(),win,lose,draw,moneyAmount);
      }
        exit(0);
    }
    else
      continue;
    /*
    switch(myNum)
    {        
      case scissors:
        break;
      case rock:
        break;
      case paper:
        break;
      case quit:
        printf("게임을 종료합니다\n");
        exit(0);
        }
    */
  }
  
  return myNum;
}


int whoIsWinner(int com, int you)
{

  
  
  if(com == 1 && you == 3 || com == 2 && you == 1 || com == 3 && you == 2)
  {
    printf("[-] 유후! 당신이 졌습니다!\n");
    comWinMoneyAccount();
    return -1;
  }
  else if (com == 1 && you == 2 || com == 2 && you == 3 || com == 3 && you == 1)
  {
    printf("[+] 흠.. 당신이 이겼습니다!\n");
    youWinMoneyAccount();
    return 1;
  }
  else
  {
    printf("[0] 헤헷 비겼습니다!\n");
    return 0;
  }
}

/* end of line */
