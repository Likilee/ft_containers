#include "RBT.h"
#include <stdlib.h>
void RBT_SET()
{
	NIL = (RBTNode*)malloc(sizeof(RBTNode));
	NIL->color = BLACK;
}

void RBT_RotateRight(RBTNode** root, RBTNode* parent)
{
	RBTNode* leftChild = parent->left;

	parent->left = leftChild->right;//왼쪽 자식의 오른쪽 자식 노드를 부모 노드의 왼쪽으로 등록

	if (leftChild->right != NIL)
		leftChild->right->parent = parent;

	leftChild->parent = parent->parent;

	if (parent->parent == NULL)//부모가 NULL일 경우 왼쪽 자식을 루트로 변경
		(*root) = leftChild;
	else
	{
		if (parent == parent->parent->left)//왼쪽 자식 노드를 부모가 있던 곳에 위치시킴.
			parent->parent->left = leftChild;
		else
			parent->parent->right = leftChild;
	}
	leftChild->right = parent;
	parent->parent = leftChild;

}

void RBT_RotateLeft(RBTNode** root, RBTNode* parent)
{
	RBTNode* rightChild = parent->right;

	parent->right = rightChild->left;//왼쪽 자식의 오른쪽 자식 노드를 부모 노드의 왼쪽으로 등록

	if (rightChild->left != NIL)
		rightChild->left->parent = parent;

	rightChild->parent = parent->parent;

	if (parent->parent == NULL)//부모가 NULL일 경우 오른쪽 자식을 루트로 변경
		(*root) = rightChild;
	else
	{
		if (parent == parent->parent->right)//오른쪽 자식 노드를 부모가 있던 곳에 위치시킴.
			parent->parent->right = rightChild;
		else
			parent->parent->left = rightChild;
	}
	rightChild->left = parent;
	parent->parent = rightChild;

}