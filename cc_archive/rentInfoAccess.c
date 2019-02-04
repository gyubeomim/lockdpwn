/*
  Name :rentInfoAccess.c ver 1.1
   Content : 영화 DVD 대여 정보 저장/참조 함수들의 정의 
   Implementation : LKB
   Last modified 2016/07/10
*/
#include "common.h"
#include "rentInfo.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"
#include "screenOut2.h"

#define RENT_LEN 100

static dvdRentInfo rentList[RENT_LEN];
static int numOfRentCus = 0;

void addRentList(char *ISBN, char *cusID ,int rentDay)
{
  strcpy(rentList[numOfRentCus].cusID, cusID);
  rentList[rentCusNum].rentDay = rentDay;

  numOfRentCus++;
}

void printOutRentAllCusInfo(char *ISBN)
{
  
  if(strcmp(rentList[numOfRentCus].ISBN,ISBN) != 0)
  {
    puts("존재하지 않는 ISBN입니다.");
    return;
  }

  for(int i =0 ; i< numOfRentCus ; i++)
  {
    printf("대여일 : %d\n",rentList[numOfRentCus].rentDay);
    ptrCusInfo = getCusPtrById(rentList[numOfRentCus].cusID);
    showCustomerInfoContinue(ptrCusInfo);
  }
   puts("[*] 조회를 완료했습니다");
}

void printOutCusAllRentInfo(char *ID, unsigned in start, unsigned int end)
{
  
}
/* end of file */
