#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"
#include "Point.h"

int WhoIsPrecede(Point * d1, Point * d2)
{
	if(d1->xpos < d2->xpos)
	{
		return 0;
	}
	else if(d1->xpos == d2->xpos)
	{
		if(d1->ypos < d2->ypos)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}


int main(void)
{
	List list;
	Point comp;
	Point * pPoint;
	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede);     // 정렬기준을 등록!

	pPoint = (Point*)malloc(sizeof(Point));
	SetPointPos(pPoint, 3, 2);
	LInsert(&list, pPoint);

	pPoint = (Point*)malloc(sizeof(Point));
	SetPointPos(pPoint, 3, 1);
	LInsert(&list, pPoint);

	pPoint = (Point*)malloc(sizeof(Point));
	SetPointPos(pPoint, 2, 2);
	LInsert(&list, pPoint);

	pPoint = (Point*)malloc(sizeof(Point));
	SetPointPos(pPoint, 2, 1);
	LInsert(&list, pPoint);

	printf("현재 데이터의 수: %d \n", LCount(&list));

	if(LFirst(&list, &pPoint))
	{
		ShowPointPos(pPoint);
		
		while(LNext(&list, &pPoint))
			ShowPointPos(pPoint);
	}
	printf("\n");

	// xpos가 2인 모든 데이터 삭제  ////////
	comp.xpos = 2;
	comp.ypos = 0;

	if(LFirst(&list, &pPoint))
	{
		if(PointComp(pPoint, &comp) == 1)
		{
			pPoint = LRemove(&list);
			free(pPoint);
		}
		
		while(LNext(&list, &pPoint))
		{
			if(PointComp(pPoint, &comp) == 1)
			{
				pPoint = LRemove(&list);
				free(pPoint);
			}
		}
	}

	// 삭제 후 저장된 데이터 출력 ////////
	printf("현재 데이터의 수: %d \n", LCount(&list));

	if(LFirst(&list, &pPoint))
	{
		ShowPointPos(pPoint);
		
		while(LNext(&list, &pPoint))
			ShowPointPos(pPoint);
	}
	printf("\n");

	return 0;
}