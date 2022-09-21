
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode* L, * R; // L : left , R : right
}TreeNode;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 }; // ��Ʈ ���
TreeNode* root = &n6;

void preorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		printf("[%d] ", temp->data);
		preorder(temp->L);
		preorder(temp->R);
	}
}

void inorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		inorder(temp->L);
		printf("[%d] ", temp->data);
		inorder(temp->R);
	}
}

void postorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		postorder(temp->L);
		postorder(temp->R);
		printf("[%d] ", temp->data);
	}
}
TreeNode* getNode(TreeNode* tree) {
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
	if (p == NULL) {
		fprintf(stderr, "���� �Ҵ� ����\n");
		exit(1);
	}
	p->data = tree->data;
	p->L = tree->L;
	p->R = tree->R;

	return p;
}
int main() {
	printf("���� ��ȸ = ");
	inorder(root);
	printf("\n");

	printf("���� ��ȸ = ");
	preorder(root);
	printf("\n");

	printf("���� ��ȸ = ");
	postorder(root);
	printf("\n");

	return 0;
}
