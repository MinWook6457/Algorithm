#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *L, *R;
}TreeNode;

#define SIZE 100
int top = -1;
TreeNode *stack[SIZE]; // 구조체 포인터 배열 선언

void push(TreeNode *p) {
	if (top < SIZE - 1)
		stack[++top] = p;
}

TreeNode *pop() {
	TreeNode *p = NULL;
	if (top >= 0)
		p = stack[top--];
	return p;
}

void inorder_iteration(TreeNode *root) {
	while (1) {
		for (;root;root = root->L)
			push(root);

		root = pop();
		if (!root)
			break;
		printf("[%d] ", root->data);
		root = root->R;
	}
}

void main() {
	TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n4 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n5 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n6 = (TreeNode*)malloc(sizeof(TreeNode));

	n6->data = 15;
	n6->L = n2;
	n6->R = n5;

	n2->data = 4;
	n2->L = n1;
	n2->R = NULL;

	n1->data = 1;
	n1->L = NULL;
	n1->R = NULL;

	n5->data = 20;
	n5->L = n3;
	n5->R = n4;

	n3->data = 16;
	n3->L = NULL;
	n3->R = NULL;

	n4->data = 25;
	n4->L = NULL;
	n4->R = NULL;
	TreeNode *root = n6;
	printf("중위 순회 = ");
	inorder_iteration(root);
}