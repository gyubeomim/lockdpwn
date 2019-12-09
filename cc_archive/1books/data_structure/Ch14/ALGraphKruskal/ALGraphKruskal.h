#ifndef __AL_GRAPH_KRUSKAL__
#define __AL_GRAPH_KRUSKAL__

#include "DLinkedList.h"
#include "PriorityQueue.h"

#include "ALEdge.h"

// 정점의 이름들을 상수화
enum {A, B, C, D, E, F, G, H, I, J};

typedef struct _ual
{
	int numV;
	int numE;
	List * adjList;
	int * visitInfo;
	PQueue pqueue;    // 간선의 가중치 정보 저장
} ALGraph;

// 그래프의 초기화
void GraphInit(ALGraph * pg, int nv);

// 그래프의 리소스 해제
void GraphDestroy(ALGraph * pg);

// 간선의 추가
void AddEdge(ALGraph * pg, int fromV, int toV, int weight);

// 간선의 정보 출력
void ShowGraphEdgeInfo(ALGraph * pg);

// Depth First Search: 정점의 정보 출력
void DFShowGraphVertex(ALGraph * pg, int startV);

// 크루스칼 최소 비용 신장 트리의 구성
void ConKruskalMST(ALGraph * pg);

// 간선의 가중치 정보 출력
void ShowGraphEdgeWeightInfo(ALGraph * pg);

#endif