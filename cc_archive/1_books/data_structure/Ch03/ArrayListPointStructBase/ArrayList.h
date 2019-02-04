#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#include "Point.h"     // 첫 번째 변경

#define TRUE	1
#define FALSE	0

#define LIST_LEN	100

// typedef int LData;
typedef Point * LData;     // 두 번째 변경

typedef struct __ArrayList
{
	LData arr[LIST_LEN];
	int numOfData;
	int curPosition;
} ArrayList;


typedef ArrayList List;

void ListInit(List * plist);
void LInsert(List * plist, LData data);

int LFirst(List * plist, LData * pdata);
int LNext(List * plist, LData * pdata);

LData LRemove(List * plist);
int LCount(List * plist);

#endif