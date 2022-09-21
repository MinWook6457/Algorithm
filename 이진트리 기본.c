
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode *L, *R; // L : left , R : right
}TreeNode;
int main()
{
	TreeNode *n1, *n2, *n3;
	n1 = (TreeNode*)malloc(sizeof(TreeNode));
	if (n1 == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
	}
	n2 = (TreeNode*)malloc(sizeof(TreeNode));
	if (n2 == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
	}
	n3 = (TreeNode*)malloc(sizeof(TreeNode));
	if (n3 == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
	}
	n1->data = 10;
	n1->L = n2;
	n1->R = n3;

	n2->data = 20;
	n2->L = NULL;
	n2->R = NULL;

	n3->data = 30;
	n3->L = NULL;
	n3->R = NULL;

	printf("  %d\n", n1->data);
	printf(" / |\n");
	printf("%d %d", n1->L->data, n1->R->data);

	free(n1);
	free(n2);
	free(n3);
	return 0;
}
