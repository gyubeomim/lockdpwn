#ifndef __DEQUE_BASE_QUEUE_H__
#define __DEQUE_BASE_QUEUE_H__

#include "Deque.h"

typedef Deque Queue;

void QueueInit(Queue * pq);
int QIsEmpty(Queue * pq);

void Enqueue(Queue * pq, Data data);
Data Dequeue(Queue * pq);
Data QPeek(Queue * pq);

#endif