#include <stdio.h>
#include <stdlib.h>
typedef int BTData;
typedef struct _bTreeNode {
	BTData data;
	struct _bTreeNode *left;
	struct _bTreeNode *right;

}BTreeNode;

BTreeNode *MakeBTreeNode() {
	BTreeNode *nd = (BTreeNode *)malloc(sizeof(BTreeNode));
	nd->left = NULL;
	nd->right = NULL;
	return nd;
}

BTData getData(BTreeNode *bt) {
	return bt->data;
}

void setData(BTreeNode *bt, BTData data) {
	bt->data = data;
}

BTreeNode *getRightSubTree(BTreeNode *bt) {
	return bt->right;
}

BTreeNode *getLeftSubTree(BTreeNode *bt) {
	return bt->left;
}
// 왼쪽 또는 오른쪽 서브트리가 존재한다면,
// 해당 트리를 삭제하고 새로운 왼쪽 또는 오른쪽 서브트리를 연결한다.
void MakeLeftSubtree(BTreeNode *main, BTreeNode *sub) {
	if (main->left != NULL)
		free(main->left);

	main->left = sub;
}

void MakeRightSubtree(BTreeNode *main, BTreeNode *sub) {
	if (main->right != NULL)
		free(main->right);

	main->right = sub;
}


void main() {
	BTreeNode *bt1 = MakeBTreeNode();
	BTreeNode *bt2 = MakeBTreeNode();
	BTreeNode *bt3 = MakeBTreeNode();
	BTreeNode *bt4 = MakeBTreeNode();

	setData(bt1, 1);
	setData(bt2, 2);
	setData(bt3, 3);
	setData(bt4, 4);
	
	MakeLeftSubtree(bt1, bt2);
	MakeRightSubtree(bt1, bt3);
	MakeLeftSubtree(bt2, bt4);
	//		bt1
	//	   /   |
	//    bt2  bt3
	//   /
	//  bt4

	printf("%d \n", getData(getLeftSubTree(bt1))); //bt1의 왼쪽 노드의 값
}