/*
  Name :dvdInfo.h ver 1.1
   Content : 영화 DVD 관리 구조체
   Implementation : LKB
   Last modified 2016/07/09
*/
#ifndef __DVDINFO_H__
#define __DVDINFO_H__

#include "cusInfo.h"

#define ISBN_LEN 30
#define TITLE_LEN 30

enum{ACTION = 1, COMIC, SF, ROMANTIC};
enum{RENTED, RETURNED};

typedef struct __dvdInfo
{
  char ISBN[ISBN_LEN];
  char title[TITLE_LEN];
  int genre;

  int rentState ;
} dvdInfo;

#endif
/* end of file */
