/*
  자료구조 p260 원형 큐의 구현 중에서
  원형 큐 헤더 파일 선언
 */

#ifndef __C_QUEUE_H__
#define __C_QUEUE_H__

#define TRUE 1
#define FALSE 0


#define QUE_LEN 100

typedef int Data;


typedef struct _cQueue
{
     int front;
     int rear;
     Data queArr[QUE_LEN];
} CQueue;


typedef CQueue Queue;

// ADT 선언
void queueInit(Queue *pq);
int qIsEmpty(Queue *pq);

void enQueue(Queue *pq, Data data);
Data deQueue(Queue *pq);
Data qPeek(Queue *pq);


#endif
