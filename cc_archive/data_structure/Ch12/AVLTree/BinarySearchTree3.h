#ifndef __BINARY_SEARCH_TREE3_H__
#define __BINARY_SEARCH_TREE3_H__

#include "BinaryTree3.h"

typedef BTData	BSTData;

// 이진 탐색 트리의 생성 및 초기화
void BSTMakeAndInit(BTreeNode ** pRoot);

// 노드에 저장된 데이터 반환
BSTData BSTGetNodeData(BTreeNode * bst);

// 이진 탐색 트리를 대상으로 데이터 저장(노드의 생성과정 포함)
void BSTInsert(BTreeNode ** pRoot, BSTData data);

// 이진 탐색 트리를 대상으로 데이터 탐색
BTreeNode * BSTSearch(BTreeNode * bst, BSTData target);

// 트리에서 노드를 제거하고 제거된 노드의 주소 값을 반환한다. 
BTreeNode * BSTRemove(BTreeNode ** pRoot, BSTData target);

// 이진 탐색 트리에 저장된 모든 노드의 데이터를 출력한다.
void BSTShowAll(BTreeNode * bst);

#endif