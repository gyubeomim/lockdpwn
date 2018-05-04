#ifndef __LB_STACK_H__
#define __LB_STACK_H__

#include "BinaryTree2.h"

#define TRUE	1
#define FALSE	0

// typedef int Data;
typedef BTreeNode * Data;

typedef struct _node
{
	Data data;
	struct _node * next;
} Node;

typedef struct _listStack
{
	Node * head;
} ListStack;


typedef ListStack Stack;

void StackInit(Stack * pstack);
int SIsEmpty(Stack * pstack);

void SPush(Stack * pstack, Data data);
Data SPop(Stack * pstack);
Data SPeek(Stack * pstack);

#endif