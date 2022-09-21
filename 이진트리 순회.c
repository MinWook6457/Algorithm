
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
TreeNode n6 = { 15, &n2, &n5 }; // 루트 노드
TreeNode* root = &n6;

void preorder(TreeNode* temp) { // 전위 순회
	if (temp != NULL) {
		printf("[%d] ", temp->data);
		preorder(temp->L);
		preorder(temp->R);
	}
}

void inorder(TreeNode* temp) { // 중위 순회
	if (temp != NULL) {
		inorder(temp->L);
		printf("[%d] ", temp->data);
		inorder(temp->R);
	}
}

void postorder(TreeNode* temp) { // 후위 순회
	if (temp != NULL) {
		postorder(temp->L);
		postorder(temp->R);
		printf("[%d] ", temp->data);
	}
}
TreeNode* getNode(TreeNode* tree) {
	TreeNode* p = (TreeNode*)malloc(sizeof(TreeNode));
	if (p == NULL) {
		fprintf(stderr, "동적 할당 실패\n");
		exit(1);
	}
	p->data = tree->data;
	p->L = tree->L;
	p->R = tree->R;

	return p;
}
int main() {
	printf("중위 순회 = ");
	inorder(root);
	printf("\n");

	printf("전위 순회 = ");
	preorder(root);
	printf("\n");

	printf("휘위 순회 = ");
	postorder(root);
	printf("\n");

	return 0;
}
