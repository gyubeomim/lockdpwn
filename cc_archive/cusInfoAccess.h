/*
  Name :cusInfoAccess.h ver 1.0
   Content : 고객 정보 저장 및 참조 함수들의 정의 선언
   Implementation : LKB
   Last modified 2016/07/09
*/


#ifndef __CUSACCESS_H__
#define __CUSACCESS_H__

#include "cusInfo.h"

int addCusInfo(char *ID, char *name, char *num);
cusInfo * getCusPtrById(char *ID);
int isRegistId(char *ID);


#endif

/* end of file */
