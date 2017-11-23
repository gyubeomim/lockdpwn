/*
  Name : phoneFunc.h ver 1.1
  Content : 전화번호 컨트롤 함수들의 선언
  Implementation : LKB
  Last modified 2016/07/06
*/




#ifndef __PHONEFUNC_H__


#define __PHONEFUNC_H__

#include "phoneData.h"

void InputPhoneData();
void ShowAllData();
void SearchPhoneData();
void DeletePhoneData();

void storeDataToFile();
void loadDataFromFile();
void storeDataToFileInStruct();
void loadDataFromFileInStruct();
void changePhoneData();


#endif

/* end of file */
