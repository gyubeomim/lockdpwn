/*
  Name :cusManager.c ver 1.0
   Content : 고객 관련 업무 처리 함수들의 정의
   Implementation : LKB
   Last modified 2016/07/09
*/
#include "common.h"
#include "cusInfo.h"
#include "cusInfoAccess.h"
#include "screenOut2.h"

void registCustomer()
{
  char tmpId[ID_LEN];
  char tmpName[NAME_LEN];
  char tmpPhone[PHONE_LEN];

  while(1)
  {
    printf("ID 입력: ");
    scanf("%s",tmpId);

    if(isRegistId(tmpId))
    {
      printf("[-] 해당 ID는 사용 중입니다. 다른 ID를 선택해주세요\n");
      continue;
    }
    
    printf("이름 입력: ");
    scanf("%s",tmpName);
    printf("전화번호 입력: ");
    scanf("%s",tmpPhone);

    if((strlen(tmpId)) < ID_LEN && (strlen(tmpName)) < NAME_LEN && (strlen(tmpPhone)) < PHONE_LEN)
    {
      break;
    }
    else
    {
      continue;
    }
  }
  
  addCusInfo(tmpId,tmpName,tmpPhone);
  printf("[+] 가입이 완료됐습니다\n");
}

void searchCusInfo()
{
  char searchId[ID_LEN];
  cusInfo *cusPtr;

  printf("찾는 ID 입력: ");
  scanf("%s",searchId);
  
  cusPtr = getCusPtrById(searchId);

  if(cusPtr == 0)
  {
    puts("존재하지 않는 사용자입니다");
    return;
  }

  showCustomerInfo(cusPtr);
}


/* end of file */
