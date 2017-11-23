#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List *plist)
{
     plist->head = NULL;
     plist->numOfData =0 ;
     plist  = 0 ;
     plist = 0 ;
}

void LInsert(List *plist, LData data)
{
     Node *newNode = (Node*)malloc(sizeof(Node));

     newNode->data = data;

     if(plist->tail == NULL)
     {
          plist->tail = newNode;
          newNode->next = newNode;
     }
     
     // LInsert와 LInsertFront의 유일한 차이점
     else
     {
          newNode->next = plist->tail->next;
          plist->tail->next = newNode;
          
          // 유일하게 이것만 다르다. tail을 새로 설정하기 위한 코드를 추가한다
          plist->tail = newNode;
     }

     (plist->numOfData)++;
}

void LInsertFront(List *plist, LData data)
{
     Node *newNode = (Node*)malloc(sizeof(Node));

     newNode->data = data;

     if(plist->tail == NULL)
     {
          plist->tail = newNode;
          newNode->next = newNode;
     }
     
     // LInsert와 LInsertFront의 유일한 차이점
     else
     {
          newNode->next = plist->tail->next;
          plist->tail->next = newNode;          
     }

     (plist->numOfData)++;
}

int LFirst(List *plist, LData *pdata)
{
     if(plist->head->next ==NULL)
     {
          return FALSE;
     }

     plist->before = plist->head;
     plist->cur = plist->head->next;

     *pdata = plist->cur->data;
     return TRUE;
}

int LNext(List *plist, LData *pdata)
{
     if(plist->cur->next == NULL)
     {
          return FALSE;
     }

     plist->before = plist->cur;
     plist->cur = plist->cur->next;

     *pdata = plist->cur->data;
     return TRUE;
}

LData LRemove(List *plist)
{
     Node *rpos = plist->cur;
     LData rdata = rpos->data;

     plist->before->next = plist->cur->next;
     plist->cur = plist->before;

     free(rpos);
     (plist->numOfData)--;
     return rdata;
}

int LCount(List *plist)
{
     return plist->numOfData;
}

void setSortRule(List *plist,int (*comp)(LData d1, LData d2))
{
     plist->comp = comp; 
}
