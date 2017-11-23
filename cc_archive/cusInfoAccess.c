/*
  Name :cusInfoAccess.c ver 1.0
   Content : 고객 정보 저장 및 참조 함수들의 정의
   Implementation : LKB
   Last modified 2016/07/09
*/
#include "common.h"
#include "cusInfo.h"

#define MAX_CUSTOMER 100

static cusInfo *cusList[MAX_CUSTOMER];
static int numOfCustomer = 0;

int addCusInfo(char *ID, char * name, char *num)
{
  cusInfo *pCus;

  if(numOfCustomer >= MAX_CUSTOMER)
  {
    return 0;
  }
  
  pCus = (cusInfo*)malloc(sizeof(cusInfo));
  
  strcpy(pCus->ID,ID);
  strcpy(pCus->name,name);
  strcpy(pCus->phoneNum,num);

  cusList[numOfCustomer++] = pCus;

  return numOfCustomer;
}

cusInfo * getCusPtrById(char *ID)
{
  for(int i=0; i<numOfCustomer; i++)
  {
    if(!strcmp(cusList[i]->ID,ID))
    {
      return cusList[i];
    }
  }

  return (cusInfo*)0;
}

int isRegistId(char *ID)
{
  cusInfo * pCus = getCusPtrById(ID);

  if(pCus == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}
