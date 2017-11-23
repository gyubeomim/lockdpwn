/*
  Name :rentInfoAccess.h ver 1.1
   Content : 영화 DVD 대여 정보 함수 선언
   Implementation : LKB
   Last modified 2016/07/10
*/



#ifndef __RENTINFOACCESS_H__
#define __RENTINFOACCESS_H__


#include "rentInfo.h"



void addRentList(char *ISBN, char *cusID, int rentDay);
void printOutRentAllCusInfo(char *ISBN);
void printOutCusAllRentInfo(char *ID, unsigned int strart, unsigned int end);

dvdRentInfo *getRentPtrByISBN(char *ISBN);
int getRentCusNum();


#endif

/* end of file */
