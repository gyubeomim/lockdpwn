/*
  Name :dvdInfoAccess.c ver 1.0
   Content : DVD 정보 저장 및 참조 함수들의 정의
   Implementation : LKB
   Last modified 2016/07/09
*/
#include "common.h"
#include "dvdInfo.h"
#include "screenOut2.h"
#include "dvdInfoAccess.h"

#define MAX_DVD 100

static dvdInfo *dvdList[MAX_DVD];
static int numOfDvd = 0;

int addDvdInfo(char *ISBN, char * title, int genre)
{
  dvdInfo *pDvd;

  if(numOfDvd >= MAX_DVD)
  {
    return 0;
  }
  
  pDvd = (dvdInfo*)malloc(sizeof(dvdInfo));
  
  strcpy(pDvd->ISBN,ISBN);
  strcpy(pDvd->title,title);
  pDvd->genre = genre;

  // 렌트용 코드 추가
  pDvd->rentState = RETURNED;
  pDvd->numOfRentCus = 0;

  dvdList[numOfDvd++] = pDvd;

  return numOfDvd;
}

dvdInfo * getDvdPtrByISBN(char *ISBN)
{
  for(int i=0; i<numOfDvd; i++)
  {
    if(!strcmp(dvdList[i]->ISBN,ISBN))
    {
      return dvdList[i];
    }
  }
  // 무슨 의미일까...?
  return (dvdInfo*)0;
}

int isRegistISBN(char *ISBN)
{
  dvdInfo * pDvd = getDvdPtrByISBN(ISBN);

  if(pDvd == 0)
  {
    return 0;
  }
  else
  {
    return -1;
  }
}

int setDVDRented(char *ISBN, char *cusID, int rentDay)
{
  dvdInfo * pDvd = getDvdPtrByISBN(ISBN);

  if(pDvd == 0)
  {
    return 0;
  }
  
  addRentList(ISBN,cusID,rentDay);
  pDvd->rentState = RENTED;
  strcpy(pDvd->rentList[rentCusNum].cusID, cusID);

  return 1;
}

int setDVDReturned(char *ISBN)
{
  dvdInfo *pDvd = getDvdPtrByISBN(ISBN);

  if(pDvd == 0)
  {
    return 0;
  }
  pDvd->rentState = RETURNED;
  return 1;
}

int getDVDRentState(char * ISBN)
{
  dvdInfo *pDvd = getDvdPtrByISBN(ISBN);

  if(pDvd == 0)
  {
    return 0;
  } 

  return pDvd->rentState;
}

/* end of file */


