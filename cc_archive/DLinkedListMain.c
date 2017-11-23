#include <stdio.h>
#include "DLinkedList.h"

int whoIsPrecede(int d1, int d2)
{
  if(d1<d2)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

void main(int argc, char *argv[])
{
  List list;
  int data;
  
  ListInit(&list);

  setSortRule(&list,whoIsPrecede);

  LInsert(&list,11); LInsert(&list,11);
  LInsert(&list,22); LInsert(&list,22);
  LInsert(&list,33);
  LInsert(&list,11); LInsert(&list,11);
  LInsert(&list,44); LInsert(&list,22);
  LInsert(&list,33);
  LInsert(&list,55); LInsert(&list,11);
  LInsert(&list,22); LInsert(&list,22);
  LInsert(&list,77);
  LInsert(&list,66); LInsert(&list,11);
  LInsert(&list,66); LInsert(&list,22);
  LInsert(&list,33);

  printf("현재 데이터의 수: %d\n",LCount(&list));

  if(LFirst(&list,&data))
  {
    printf("%d ",data);

    while(LNext(&list,&data))
    {
      printf("%d ",data);
    }
  }
  printf("\n\n");

  // 숫자 22를 검색하여 모두 삭제한다
  if(LFirst(&list,&data))
  {
    if(data == 22)
    {
      LRemove(&list);
    }
    while(LNext(&list,&data))
    {
      if(data == 22)
      {
        LRemove(&list);
      }
    }
  }

  // 삭제 후 남아있는 데이터 전체를 출력한다
  printf("현재 데이터의 수: %d\n",LCount(&list));

  if(LFirst(&list,&data))
  {
    printf("%d ",data);

    while(LNext(&list,&data))
    {
      printf("%d ",data);
    }
  }
  printf("\n\n");
}
