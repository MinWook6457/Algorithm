#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#pragma warning(disable:4996)수
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode *newNode(int item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
int arr[1024];
int nCount = 0;
void in_order(TreeNode *temp) {
	if (temp == NULL)
		return;
	in_order(temp->left);
	arr[nCount++] = temp->data;
	in_order(temp->right);
}
bool checkBTN(TreeNode *root) {
	in_order(root);

	for (int i = 0; i < nCount; i++) {
		if (arr[i] >= arr[i + 1])
			return false;
	}
	return true;
}
void insert_node(TreeNode** root, int key) {

	TreeNode* p, *t; // p는 t의 부모노드 t는 현재위치

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (key == t->data) // 새로 추가하려는 단어가 이미 트리에 있는 경우
			return;
		p = t; // *** 부모 노드 업데이트 ***
		if (key < t->data)
			t = t->left;
		else
			t = t->right;
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}

	n->data = key;
	printf("inserted %d\n", n->data);
	n->left = n->right = NULL;

	if (p != NULL) {
		if (key < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else {
		*root = n;
	}
}

void preorder(TreeNode* temp) { // 전위 순회
	if (temp != NULL) {
		printf("%d ", temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}


bool check_binary_tree(TreeNode *temp,int max,int min) {
	if (temp->data < min || temp->data >= min)
		return false;

	if (temp->left != NULL && !check_binary_tree(temp->left, temp->data, min)) {
		return false;
	}

	if (temp->right != NULL && !check_binary_tree(temp->right, max, temp->data)) {
		return false;
	}

	return true;
}
void main() {
	TreeNode *root = NULL;
	
	FILE *fp;
	fp = fopen("ddata.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}
	int temp;
	while (!feof(fp)) {
		fscanf(fp, "%d ", &temp);
		insert_node(&root, temp);
	}

	preorder(root);
	printf("\n");
	if (checkBTN(root)==false)
		printf("완전 이진 트리 입니다\n");
	else
		printf("완전 이진 트리가 아닙니다\n");
	printf("최소값 : %d  최대값 : %d", arr[0], arr[nCount - 1]);
}