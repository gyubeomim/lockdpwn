#include "doublylist.h"

DoublyList* createDoublyList()
{
	DoublyList* pReturn = NULL;

	pReturn = (DoublyList*)malloc(sizeof(DoublyList));

	if (pReturn != NULL)
	{
		memset(pReturn, 0, sizeof(DoublyList));

		pReturn->headerNode.pLLink = &(pReturn->headerNode);
		pReturn->headerNode.pRLink = &(pReturn->headerNode);
	}
	else
	{
		printf("createDoublyList() Error! 메모리 할당 실패 \n");
	}

	return pReturn;
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element)
{
	int i = 0;
	int ret = FALSE;

	DoublyListNode *pNewNode = NULL;
	DoublyListNode *pPreNode = NULL;

	if (pList != NULL)
	{
		if (position >= 0 && position <= pList->curElementCnt)
		{
			pNewNode = (DoublyListNode*)malloc(sizeof(DoublyListNode));

			if (pNewNode != NULL)
			{
				//pNewNode 초기화
				*pNewNode = element;
				pNewNode->pLLink = NULL;
				pNewNode->pRLink = NULL;

				//pPreNode 탐색
				pPreNode = &(pList->headerNode);

				for (i = 0; i<position; i++)
				{
					pPreNode = pPreNode->pRLink;
				}

				pNewNode->pLLink = pPreNode;
				pNewNode->pRLink = pPreNode->pRLink;
				pNewNode->pRLink->pLLink = pNewNode;
				pNewNode->pLLink->pRLink = pNewNode;

				pList->curElementCnt++;
				ret = TRUE;
			}
			else
			{
				printf("addDLElement Error! newNode 할당 실패 \n");
			}
		}
		else
		{
			printf("addDLElement Error! newNode 할당 실패  position(%d) 위치 Error \n", position);
		}
	}

	return ret;
}

int removeDLElement(DoublyList* pList, int position)
{
	int i = 0;
	int ret = FALSE;

	DoublyListNode *pDelNode = NULL;

	if (pList != NULL)
	{
		if (position >= 0 && position < pList->curElementCnt)
		{
			pDelNode = &(pList->headerNode);
			for (i = 0; i <= position; i++)
			{
				pDelNode = pDelNode->pRLink;
			}

			pDelNode->pLLink->pRLink = pDelNode->pRLink;
			pDelNode->pRLink->pLLink = pDelNode->pLLink;
			free(pDelNode);

			pList->curElementCnt--;
			ret = TRUE;
		}
		else
		{
			printf("removeElement Error! position(%d)위치 \n", position);
		}
	}

	return ret;
}

DoublyListNode* getDLElement(DoublyList* pList, int position)
{
	int i = 0;

	DoublyListNode* pReturn = NULL;

	if (pList != NULL)
	{
		if (position >= 0 && position < pList->curElementCnt)
		{
			pReturn = &(pList->headerNode);
			for (i = 0; i <= position; i++)
				pReturn = pReturn->pRLink;
		}
		else
		{
			printf("getDLElement Error! position(%d) \n", position);
		}
	}

	return pReturn;
}

void displayDoublyList(DoublyList* pList)
{
	int i = 0;

	if (pList != NULL)
	{
		printf("현재 노드 갯수 : %d \n", pList->curElementCnt);

		for (i = 0; i<pList->curElementCnt; i++)
		{
			printf("[%d] : %d \n", i, getDLElement(pList, i)->data);
		}
	}
	else
	{
		printf("원소가 없습니다. \n");
	}
}

void deleteDoublyList(DoublyList* pList)
{
	if (pList != NULL)
	{
		clearDoublyList(pList);
		free(pList);
	}
}

void clearDoublyList(DoublyList* pList)
{
	if (pList != NULL)
	{
		while (pList->curElementCnt > 0)
		{
			removeDLElement(pList, 0);
		}
	}
}

int getDoublyListLength(DoublyList* pList)
{
	int ret = 0;

	if (pList != NULL)
	{
		ret = pList->curElementCnt;
	}

	return ret;
}

