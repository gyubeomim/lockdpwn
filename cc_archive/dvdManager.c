/*
  Name :dvdManager.c ver 1.0
   Content : DVD 관련 업무 처리 함수들의 정의
   Implementation : LKB
   Last modified 2016/07/09
*/


#include "common.h"
#include "screenOut2.h"
#include "dvdInfo.h"
#include "dvdInfoAccess.h"

// DVD 대여로 추가된 선언
#include "cusInfoAccess.h"
#include "rentInfo.h"


void registDvd()
{
  
  char tmpISBN[ISBN_LEN];
  char tmpTitle[TITLE_LEN];
  int tmpGenre;
  

  while(1)
  {
    printf("ISBN 입력: ");
    scanf("%s",tmpISBN);
    printf("제목 입력: ");

    // scanf로 공백까지 입력하려면 아래 두 줄이 필요하다
    getchar();
    scanf("%[^\n]s",tmpTitle);

    
    printf("장르 입력 <액션 1, 코믹 2, SF 3, 로맨틱 4>: ");
    scanf("%d",&tmpGenre);

    if((strlen(tmpISBN) < ISBN_LEN && (strlen(tmpTitle)) < TITLE_LEN))
    {   
      if(!isRegistISBN(tmpISBN))
      {
        break;
      }
      else if(isRegistISBN(tmpISBN))
      {
        printf("[-] 해당 ISBN은 사용 중입니다. 다른 ISBN을 선택해주세요\n");
      }
      
    }
    
    else
    {
      continue;
    }
  
  }

  addDvdInfo(tmpISBN,tmpTitle,tmpGenre);
  printf("[+] DVD 등록이 완료됐습니다\n");
    
}


void searchDvdInfo()
{
  char searchISBN[ISBN_LEN];
  dvdInfo *dvdPtr;

  
  printf("찾는 ISBN 입력: ");
  scanf("%s",searchISBN);
  
  dvdPtr = getDvdPtrByISBN(searchISBN);

  if(dvdPtr == 0)
  {
    puts("존재하지 않는 ISBN 입니다");
    return;
  }


  showDvdInfo(dvdPtr);
}

void rentDvd()
{
  char tmpISBN[ISBN_LEN];
  int registDvd;
  int registCus;
  int rentSte;

  char tmpId[ID_LEN];
  unsigned int tmpDay;

  
  printf("[*] 대여 DVD ISBN 입력: ");
  scanf("%s",tmpISBN);

  registDvd  = isRegistISBN(tmpISBN);
  
  if(registDvd == 0)
  {
    printf("해당 DVD가 존재하지 않습니다");
    return;
  }

  rentSte = getDVDRentState(tmpISBN);

  if(rentSte = RENTED)
  {
    puts("[-] 대여 중이라 대여가 불가능합니다.");
    return;
  }

  printf("[*] 대여가 가능합니다. 대여 과정을 진행합니다.\n");
  printf("대여 고객 ID 입력: ");
  scanf("%s",tmpId);

  registCus = isRegistId(tmpId);

  if(registCus == 0)
  {
    puts("가입 고객이 아닙니다");
    return;
  }

  fputs("대여 날짜를 입력하세요: ",stdout);
  scanf("%u",&tmpDay);

  fflush(stdin);

  setDVDRented(tmpISBN,tmpId,tmpDay);
  puts("[+] 대여가 완료됐습니다");
  
  
      
  /* 
  for(int i =0; i < numOfDvd ; i++)
  {
    if(strcmp(tmpISBN,dvdList[i]) == 0 && dvdList[i].rentState == RETURNED)
    {
      printf("[*] 대여가 가능합니다. 대여 과정을 진행합니다.\n");
      printf("대여 고객 ID 입력: ");
      scanf("%s",tmpId);

      for(int j =0 ; j< numOfCustomer ; j++)
      {
        if(isRegistId(tmpId) != 0)
        {
          strcpy(dvdList[i].rentList[numOfRent++].cusID,tmpId);
          
          printf("대여 날짜 입력: ");
          scanf("%d",&tmpDay);

          dvdList[i].rentList[numOfRent++].rentDay = tmpDay;
          dvdList[i].rentState = RENTED;
          dvdList[i].numOfRentCus++;

          printf("[+] 대여가 완료됐습니다");
          return;
        }
        else
        {
          printf("[-] ID를 찾을 수 없습니다");
          return;
        }
      }
    }
    else
    {
      printf("[-] 찾는 DVD가 없습니다");
    }
  }
 
  return;
 */ 
}


void returnDvd()
{
  char tmpISBN[ISBN_LEN];
  int registDvd;
  int rentSte;

  
  printf("반납 DVD ISBN 입력: ");
  scanf("%s",tmpISBN);


  registDvd = isRegistISBN(tmpISBN);

  if(registDvd == 0)
  {
    printf("해당 DVD가 존재하지 않습니다");
    return;
  }

  rentSte = getDVDRentState(tmpISBN);

  if(rentSte == RETURNED)
  {
    puts("대여되지 않은 DVD입니다.");
    return;
  }

  setDVDReturned(tmpISBN);
  puts("[+] 반납이 완료됐습니다");

  
  /*  
  for(int i =0 ; i< numOfDvd ; i++)
  {
    if(strcmp(tmpISBN, dvdList[i]) == 0 && dvdList[i].rentState == RENTED)
    {
      
      dvdList[i].rentState = RETURNED;
      printf("[+]반납이 완료됐습니다");
      return;
    }
    else
    {
      printf("해당 DVD는 대여 중이 아니거나 존재하지 않습니다");
      return;
    }
    
  }

  return;
*/
}

void showDVDRentAllCusInfo()
{
  char tmpISBN[ISBN_LEN];
  
  printf("찾는 ISBN 입력: ");
  getchar();
  scanf("%[^\n]s",tmpISBN);


  printOutRentAllCusInfo(tmpISBN);

  puts("[*] 조회를 완료했습니다");
  
}

/* end of file */
