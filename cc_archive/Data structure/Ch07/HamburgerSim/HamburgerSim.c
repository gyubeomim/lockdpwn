#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CircularQueue.h"

#define	CUS_COME_TERM	15		// 고객의 주문 간격: 초 단위

#define CHE_BUR		0		// 치즈버거 상수 
#define BUL_BUR		1		// 불고기버거 상수
#define DUB_BUR		2		// 더블버거 상수

#define CHE_TERM	12		// 치즈버거 제작 시간: 초 단위
#define BUL_TERM	15		// 불고기버거 제작 시간: 초 단위
#define DUB_TERM	24		// 더블버거 제작 시간: 초 단위

int main(void)
{
	int makeProc=0;			// 햄버거 제작 진행상황
	int cheOrder=0, bulOrder=0, dubOrder=0;
	int sec;

	Queue que;

	QueueInit(&que);
	srand(time(NULL));

	// 아래 for문의 1회 회전은 1초의 시간 흐름을 의미함
	for(sec=0; sec<3600; sec++)
	{
		if(sec % CUS_COME_TERM == 0) 
		{
			switch(rand() % 3)
			{
			case CHE_BUR:
				Enqueue(&que, CHE_TERM);
				cheOrder += 1;
				break;

			case BUL_BUR:
				Enqueue(&que, BUL_TERM);
				bulOrder += 1;
				break;

			case DUB_BUR:
				Enqueue(&que, DUB_TERM);
				dubOrder += 1;
				break;
			}
		}

		if(makeProc==0 && !QIsEmpty(&que))
			makeProc = Dequeue(&que);

		makeProc--;
	}

	printf("Simulation Report! \n", QUE_LEN);
	printf(" - Cheese burger: %d \n", cheOrder);
	printf(" - Bulgogi burger: %d \n", bulOrder);
	printf(" - Double burger: %d \n", dubOrder);
	printf(" - Waiting room size: %d \n", QUE_LEN);
	return 0;
}