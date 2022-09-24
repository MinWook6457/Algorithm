#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
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

void preorder(TreeNode* temp) { // ���� ��ȸ
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
		fprintf(stderr, "������ �� �� �����ϴ�.\n");
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
		printf("���� ���� Ʈ�� �Դϴ�\n");
	else
		printf("���� ���� Ʈ���� �ƴմϴ�\n");
	printf("�ּҰ� : %d  �ִ밪 : %d", arr[0], arr[nCount - 1]);
}