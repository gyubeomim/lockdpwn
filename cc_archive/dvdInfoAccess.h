/*
  Name :dvdInfoAccess.h ver 1.0
   Content : DVD 정보 저장 및 참조 함수들의 선언
   Implementation : LKB
   Last modified 2016/07/09
*/



#ifndef __DVDCONTROL_H__
#define __DVDCONTROL_H__


#include "dvdInfo.h"

int addDvdInfo(char *ISBN, char *title, int genre);
dvdInfo *getDvdPtrByISBN(char *ISBN);
int isRegistISBN(char * ISBN);


int setDVDRented(char *ISBN, char *cusID, int rentDay);
int setDVDReturned(char *ISBN);
int getDVDRentState(char *ISBN);


#endif


/* end of file */
