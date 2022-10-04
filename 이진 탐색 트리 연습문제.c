#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define SIZE 30
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
void inorder(TreeNode* root) { // 중위 순회
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
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
void display(TreeNode* p) {
	if (p != NULL) {
		display(p->left);
		printf("%d ", p->data);
		display(p->right);
	}
}
int get_leaf_count(TreeNode *node) { // 단말 노드의 개수 구하는 함수
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}

	return count;
}
int get_height(TreeNode *node) { // 노드의 높이 구하는 함수
	int height = 0;

	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}
	return height;
}
bool check(TreeNode *node) {
	if (get_leaf_count(node) == (int)pow(2, get_height(node) - 1))
		return true;
	else
		return false;
}
TreeNode *min_value_node(TreeNode *node) { // 최소 키 값을 가지는 노드를 반환
	TreeNode *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
TreeNode *max_value_node(TreeNode *node) { // 최소 키 값을 가지는 노드를 반환
	TreeNode *current = node;

	while (current->right != NULL)
		current = current->right;

	return current;
}
void main() {
	TreeNode *root = NULL;
	FILE *fp;
	fp = fopen("ddata.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "파일을 열 수 없습니다.\n");
		exit(1);
	}
	int *n = (int *)malloc(sizeof(int) * SIZE);
	srand((unsigned)time(NULL));
	for (int i = 0; i < SIZE; i++) {
		n[i] = rand();
		for (int j = 0; j < i; j++) {
			if (n[i] == n[j]) 
				i--;
		}
	}
	for (int i = 0; i < SIZE; i++) {
		fprintf(fp, "%d ", n[i]);
	}
	int temp;
	rewind(fp);
	fp = fopen("ddata.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%d ", &temp);
		insert_node(&root, temp);
	}
	printf("중위 순회 : ");
	inorder(root);
	printf("\n");
	if (check(root))
		printf("\n완전 이진 트리 입니다\n");
	else
		printf("\n완전 이진 트리가 아닙니다\n");
	TreeNode *max = max_value_node(root);
	TreeNode *min = min_value_node(root);
	printf("최대값 : %d 최소값 : %d \n", max->data, min->data);
}