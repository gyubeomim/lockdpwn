/*
  Name : main2.c ver 1.0
  Content : main function
  Implementation : LKB
  Last modified 2016/07/07
*/
#include "common.h"
#include "game.h"
#include "gameTimes.h"
#include "gameMoney.h"
#include "gameContinue.h"

int main()
{
  int com;
  int you;
  int win =0 ,lose =0 ,draw =0 ;
  int state[4] ={0};
  int initMoneyAmount = 1000;
  int moneyAmount = 200;
  int loadFlag =0;
  int flag =0;

  system("clear");
  puts("자! 게임을 시작합니다\n");

  printf("이어서 하시겠습니까? < Yes : 1, No : 2 >: ");
  scanf("%d",&loadFlag);

  FILE *fp = fopen("game.dat","r");

  // 로드하고 시작할 경우
  if(loadFlag == 1 && fp != NULL)
  {
    state[4] = loadSavedFile();

    win=state[0] ;
    lose =state[1];
    draw = state[2];
    moneyAmount = state[3];

    printf("[*] 당신의 잔액 : [%d원], 컴퓨터의 잔액 : [%d원]\n",getCurrentYouMoney(),getCurrentComMoney());
  }

  // initMoneyAmount;
  // 로드 안하고 바로 시작할 경우
  else
  {
    while(1)
    {
      printf("기본 게임머니 금액을 설정하세요(default: 1000, Min: 100, max: 10000): ");
      scanf("%d",&initMoneyAmount);

      if(initMoneyAmount >= 100 || initMoneyAmount <= 10000)
      {
        break;
      }
      else
        continue;
    }
    setComMoney(initMoneyAmount);
    setYouMoney(initMoneyAmount);

    while(1)
    {
      printf("판돈의 크기를 정해주세요(default: 200, Min: 100, max: 5000): ");
      scanf("%d",&moneyAmount);

      if(initMoneyAmount < moneyAmount)
        continue;
    
      if(moneyAmount >= 100 || moneyAmount<= 5000)
      {
        break;
      }
      else
        continue;
    }
  
    setGamblingTableMoney(moneyAmount);
  }
  //int moneyCom = 1000, moneyMine = 1000;
  //int win=0,lose=0,draw=0;

  while(1)
  {
    puts("ooooooooo대결!ooooooooo\n");
    com = choiceOfCom();
    you = choiceOfMe(win,lose,draw,moneyAmount);
    puts("");

    if(you == 1)
      printf("당신의 선택은 [가위]\n");
    else if(you ==2)
      printf("당신의 선택은 [바위]\n");
    else if (you ==3)
      printf("당신의 선택은 [보]\n");

    
    if(com == 1)
      printf("컴퓨터의 선택은 [가위]\n");
    else if(com ==2)
      printf("컴퓨터의 선택은 [바위]\n");
    else if (com ==3)
      printf("컴퓨터의 선택은 [보]\n");

    puts("\nxxxxxxxxx결과!xxxxxxxxx\n");
    flag = whoIsWinner(com,you);

    if(flag ==1)
    {
      win++;
    }
    else if(flag == -1)
    {
      lose++;
    }
    else if(flag == 0)
    {
      draw++;
    }

    printf("[*] 승률은 %d\%\입니다.\n",calcPercent(win,lose));
    printf("[*] Count: win:[%d] lose:[%d] draw:[%d}\n",win,lose,draw);
    printf("[*] Game Money\nMe : [%d원], Com : [%d원]\n",getCurrentYouMoney(),getCurrentComMoney());

    if(getCurrentComMoney() <= 0 || getCurrentYouMoney()<=0)
    {
      break;
    }
    
    /* 
       if(moneyMine == 0)
       {
       printf("\n[-] 아깝지만 졌소..\n");
       break;
       }
       else if(moneyCom ==0)
       {
       printf("\n[+] 승리하셨습니다! 축하합니다\n");
       break;
       }
    */
    puts("");
  }
  return 0;
}


