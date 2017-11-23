/*
  Name :screenOut2.c ver 1.0
   Content : 콘솔 출력을 위한 함수들의 정의
   Implementation : LKB
   Last modified 2016/07/09
*/

#include "common.h"
#include "cusInfo.h"
#include "dvdInfo.h"
#include "dvdManager.h"
#include "dvdInfoAccess.h"

int firstFlag = 0;

void showMenu()
{
  if (firstFlag == 0 )
  {
    system("clear"); //stdlib.h
    firstFlag++;
  }
  printf("\n---------메뉴---------\n");
  printf("1. 신규가입\n");
  printf("2. 고객검색\n");
  printf("\n-----------------------\n");
  printf("3. DVD 등록\n");
  printf("4. DVD 검색\n");
  printf("\n-----------------------\n");
  printf("5. DVD 대여\n");
  printf("6. DVD 반납\n");
  printf("\n-----------------------\n");
  printf("7. DVD 대여고객 전체 조회\n");
  printf("8. 고객 대여 DVD 전체 조회\n");
  printf("9. 종료\n");
  printf("-----------------------\n");
  printf("선택>> ");
}

void showCustomerInfo(cusInfo *pCus)
{
  printf("\n**********************\n");
  printf("| >> ID : %s \n", pCus->ID);
  printf("| >> 이름 : %s \n", pCus->name);
  printf("| >> 전화번호 : %s \n", pCus->phoneNum);
  printf("**********************\n\n"); 
}

void showDvdInfo(dvdInfo *pDvd)
{
  printf("\n**********************\n");
  printf("| >> ISBN : %s \n", pDvd->ISBN);
  printf("| >> 제목 : %s \n", pDvd->title);
  printf("| >> 장르 : "); showGenre(pDvd->genre); printf("\n");
  printf("**********************\n\n");
}

void showGenre(int gen)
{
  switch(gen)
  {
    case ACTION:
      fputs("액션",stdout);
      break;
      case COMIC:
      fputs("코믹",stdout);
      break;
      case SF:
      fputs("SF",stdout);
      break;

    case ROMANTIC:
      fputs("로맨틱",stdout);
      break;
  }
}

void showCustomerInfoContinue(cusInfo *pCus)
{
  printf("\n**********************\n");
  printf("| >> ID : %s \n", pCus->ID);
  printf("| >> 이름 : %s \n", pCus->name);
  printf("| >> 전화번호 : %s \n", pCus->phoneNum); 
  printf("**********************\n\n"); 
}

/* end of file */
