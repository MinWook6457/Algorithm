#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#define SIZE 30
#pragma warning(disable:4996)��
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
void inorder(TreeNode* root) { // ���� ��ȸ
	if (root != NULL) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

void insert_node(TreeNode** root, int key) {

	TreeNode* p, *t; // p�� t�� �θ��� t�� ������ġ

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (key == t->data) // ���� �߰��Ϸ��� �ܾ �̹� Ʈ���� �ִ� ���
			return;
		p = t; // *** �θ� ��� ������Ʈ ***
		if (key < t->data)
			t = t->left;
		else
			t = t->right;
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
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
int get_leaf_count(TreeNode *node) { // �ܸ� ����� ���� ���ϴ� �Լ�
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}

	return count;
}
int get_height(TreeNode *node) { // ����� ���� ���ϴ� �Լ�
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
TreeNode *min_value_node(TreeNode *node) { // �ּ� Ű ���� ������ ��带 ��ȯ
	TreeNode *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
TreeNode *max_value_node(TreeNode *node) { // �ּ� Ű ���� ������ ��带 ��ȯ
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
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
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
	printf("���� ��ȸ : ");
	inorder(root);
	printf("\n");
	if (check(root))
		printf("\n���� ���� Ʈ�� �Դϴ�\n");
	else
		printf("\n���� ���� Ʈ���� �ƴմϴ�\n");
	TreeNode *max = max_value_node(root);
	TreeNode *min = min_value_node(root);
	printf("�ִ밪 : %d �ּҰ� : %d \n", max->data, min->data);
}