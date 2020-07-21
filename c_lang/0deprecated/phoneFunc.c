/*
  Name : phoneFunc.c ver 1.4
  Content : 전화번호 컨트롤 함수
  Implementation : LKB
  Last modified 2016/07/06
*/
#include "common.h"
#include "phoneData.h"
#include "screenOut.h"

#define LIST_NUM 100

int numOfData = 0;
phoneData *phoneList[LIST_NUM];

char name[LIST_NUM];
int j =1 ;

void InputPhoneData()
{
  phoneData *pData;
  
  if(numOfData >= LIST_NUM)
  {
    puts("[-] 메모리 공간이 부족합니다");
    return;
  }

  pData = (phoneData*)malloc(sizeof(phoneData));

  printf("이름 입력: ");
  scanf("%s",pData->name);

  printf("전화번호 입력: ");
  scanf("%s",pData->phoneNum);

  if(checkSameData(pData) == 1)
  {
    printf("\n[-] 이미 입력된 데이터입니다.\n");
    free(pData);
    return;
  }

  printf("\n[*] 입력이 완료됐습니다.\n");

  phoneList[numOfData] = pData;
  numOfData++;
  storeDataToFile();
  storeDataToFileInStruct();
  
}

void ShowAllData()
{
  for(int i=0; i<numOfData;i++)
    ShowPhoneInfoByPtr(phoneList[i]);
}


void SearchPhoneData()
{
  printf("찾는 검색어를 입력해주세요 : ");
  scanf("%s",name);

  for(int i =0; i<numOfData ; i++)
  {
    // 문자열은 strcmp로 비교할 수 있다
    if(strcmp(name,phoneList[i]->name) == 0)
    {
      ShowPhoneInfoByPtr(phoneList[i]);
    }
  }
  printf("\n[*] 검색이 완료되었습니다\n");
}


void DeletePhoneData()
{
  int num = 0;
  int numFlag =0;
  printf("지울 검색어를 입력해주세요 : ");
  scanf("%s",name);
  int j=1;

  // 이름이 같은 데이터의 갯수를 센다
  for(int i =0; i<numOfData ; i++)
  {
    if(strcmp(name,phoneList[i]->name) == 0)
    {
      num++;
    }
  }

  // 만약 일치하는 이름이 한개면
  if (num ==1)
  {
    for(int i =0; i<numOfData ; i++)
    {
      // 만약 이름이 같다면
      if(strcmp(name,phoneList[i]->name) == 0)
      {
        // 메모리 공간을 할당받았으므로 다시 반환해야 한단다..o_o
        free(phoneList[i]);
      
        // i+1이 길이의 끝에 닿을때까지 순서를 한칸씩 앞으로 당긴다
        while(i+1 <= numOfData)
        {
          phoneList[i] = phoneList[i+1];
          i++;
        }
      }
    }
  }
  
  // 만약 일치하는 이름이 두개 이상이면
  else if(num >1)
  {
    printf("\n[*] 찾는 이름이 2개 이상입니다\n");

    for(int i = 0 ; i < numOfData ; i++)
    {
      if(strcmp(name,phoneList[i]->name) == 0)
      {
        printf("NUM. %d\n",j);
        ShowPhoneInfoByPtr(phoneList[i]);
        j++;
      }
    }

    printf("원하는 번호를 선택하세요: ");
    scanf("%d",&numFlag);
  }

  // 다시 j는 1로 초기화시켜놓고
  j = 1;
  
  for(int i=0; i<numOfData;i++)
  {
    if(strcmp(name,phoneList[i]->name) == 0)
    {
        
      if(numFlag == j)
      {
        free(phoneList[i]);
      
        // [삭제 과정] i+1이 길이의 끝에 닿을때까지 순서를 한칸씩 앞으로 당긴다
        while(i+1 <= numOfData)
        {
          phoneList[i] = phoneList[i+1];
          i++;
        }
        printf("\n[*] 삭제가 완료되었습니다\n");
      }
      j++;
    }
  }
  
  numOfData--;

  storeDataToFile();
  storeDataToFileInStruct();
  
}

// 같은 이름, 전화번호가 있는지 확인해주는 함수
int checkSameData(phoneData *pPhone)
{
  if(numOfData == 0)
  {
    return 0;
  }
  
  for(int i=0; i<numOfData ;i++)
  {
    // 이름과 전화번호가 같으면 1 반환
    if(strcmp(pPhone->name,phoneList[i]->name) == 0 && strcmp(pPhone->phoneNum,phoneList[i]->phoneNum)==0)
    {
      return 1;
    }
  }

  return 0;
}

void changePhoneData()
{
  int idxOfMatchingData[LIST_NUM];
  int matchedCount = 0;
  int selection = 0;
  int changeIdx =0;

  char changeName[NAME_LEN];
  char changeNum[PHONE_LEN];
  
  fputs("찾는 이름은? : ",stdout);
  scanf("%s",changeName);
  
  for(int i=0; i<numOfData ;i++)
  {
    if (strcmp(changeName,phoneList[i]->name) == 0)
    {
      idxOfMatchingData[matchedCount++] = i;
    }
  }

  if(matchedCount == 0)
  {
    fputs("\n[-] 찾는 이름이 없습니다!\n",stdout);
    return;
  }
  else if(matchedCount==1)
  {
    changeIdx = idxOfMatchingData[0];
  }
  else
  {
    for(int i=0; i<matchedCount; i++)
    {
      printf("NUM. %d\n",i+1);
      ShowPhoneInfoByPtr(phoneList[idxOfMatchingData[i]]);
    }

    fputs("선택 : ",stdout);
    scanf("%d",&selection);
    fflush(stdin);

    changeIdx = idxOfMatchingData[selection-1];
  }


  fputs("변경할 전화번호는? : ",stdout);
  scanf("%s",changeNum);

  strcpy(phoneList[changeIdx]->phoneNum,changeNum);

  printf("\n[*] 변경이 완료됐습니다\n");

  storeDataToFile();
  storeDataToFileInStruct();
}

void storeDataToFile()
{
  FILE *fp = fopen("phoneNum.txt","w");

  fwrite(&numOfData, sizeof(int),1,fp); // 데이터의 총 개수

  for(int i=0; i<numOfData;i++)
  {
    fprintf(fp,"%s\n%s\n",phoneList[i]->name,phoneList[i]->phoneNum);
    free(phoneList[i]);
  }
 
  fclose(fp);
  
  /*
  if(fp == NULL)
  {
    return;
  }

  
  for(int i =0;i<numOfData;i++)
  {
      fprintf(fp,"%s\n%s\n",phoneList[i]->name,phoneList[i]->phoneNum);
  }
  */
}


void loadDataFromFile()
{
  FILE *fp = fopen("phoneNum.txt","r");
  
  
  if(fp == NULL)
  {
    return;
  }

  fread(&numOfData,sizeof(int),1,fp);

  for(int i =0; i<numOfData;i++)
  {
    
    phoneList[i] = (phoneData*)malloc(sizeof(phoneData));

    fscanf(fp,"%s\n%s\n",phoneList[i]->name,phoneList[i]->phoneNum);

  }

  fclose(fp);
  
  /*
    for(int i =0;;i++)
    {

    // 아.. 이것때문에 몇분을 헤멘거야.. ㅠ_ㅠ
    phoneList[i] = (phoneData*)malloc(sizeof(phoneData));
    
    if(feof(fp) != 0)
    {
    numOfData = i;
    break;
    }
    
    fscanf(fp,"%s\n%s\n",phoneList[i]->name,phoneList[i]->phoneNum);
    }
  */

}

void storeDataToFileInStruct()
{
  
}

void loadDataFromFileInStruct()
{
  
}

/* end of file */
