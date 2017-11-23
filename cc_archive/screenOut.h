/*
  Name : screenOut.h ver 1.1
  Content : 콘솔 출력을 위한 함수 선언
  Implementation : LKB
  Last modified 2016/07/06
*/


#ifndef __SCREENOUT_H__

#define __SCREENOUT_H__

#include "phoneData.h"


void ShowMenu();
void ShowPhoneInfo(phoneData phone);
void ShowPhoneInfoByPtr(phoneData *pPhone);

#endif



/* end of file */
