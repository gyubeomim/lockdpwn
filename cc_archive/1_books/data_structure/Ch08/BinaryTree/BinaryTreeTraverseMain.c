#include <stdio.h>
#include "BinaryTree.h"

void InorderTraverse(BTreeNode * bt)
{
	if(bt == NULL)    // bt°¡ NULLÀÌ¸é Àç±Í Å»Ãâ! 
		return;

	InorderTraverse(bt->left); 
	printf("%d \n", bt->data); 
	InorderTraverse(bt->right); 
}

int main(void)
{
	BTreeNode * bt1 = MakeBTreeNode();
	BTreeNode * bt2 = MakeBTreeNode();
	BTreeNode * bt3 = MakeBTreeNode();
	BTreeNode * bt4 = MakeBTreeNode();

	SetData(bt1, 1);
	SetData(bt2, 2);
	SetData(bt3, 3);
	SetData(bt4, 4);

	MakeLeftSubTree(bt1, bt2);
	MakeRightSubTree(bt1, bt3);
	MakeLeftSubTree(bt2, bt4);

	InorderTraverse(bt1);
	return 0;
}