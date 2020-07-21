/*
  Name :cusInfo.h ver 1.0
   Content : 绊按 包府 备炼眉
   Implementation : LKB
   Last modified 2016/07/09
*/


#ifndef __CUSINFO_H__
#define __CUSINFO_H__

#define ID_LEN 10
#define NAME_LEN 30
#define PHONE_LEN 30



typedef struct __cusInfo
{
  char ID[ID_LEN];
  char name[NAME_LEN];
  char phoneNum[PHONE_LEN];
} cusInfo;


#endif

/* end of file */
