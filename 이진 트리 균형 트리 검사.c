#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_height(TreeNode *node) { // 노드의 높이 구하는 함수
	int height = 0;

	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}
	return height;
}
void inorder(TreeNode *root) {
	if (!root)
		return;
	inorder(root->left);
	printf("%d ", root->data);
	inorder(root->right);
}
int isBalanced(TreeNode *root) {
	TreeNode *p = root;

	int left_h = get_height(root->left);
	int right_h = get_height(root->right);
	printf("왼쪽 서브트리 높이 : %d 오른쪽 서브트리 높이 : %d \n", left_h, right_h);
	int h = abs(left_h - right_h); // 음수가 나올 수 있으므로 절대값
	if (h <= 1) // 서브트리 간 차이가 최대 1
		return 1;
	else
		return 0;
}
TreeNode *new_node(int item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
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
int get_sum_node(TreeNode *root) {
	int sum = 0;
	if (root == NULL)
		return 0;
	sum = root->data;
	sum += get_sum_node(root->left) + get_sum_node(root->right);
	return sum;
}
void print_smaller(TreeNode* root, int value)
{	
	if (root == NULL) 
		return;
	if (root->data < value)
		printf("%d보다 작은 노드: %d\n", value, root->data);
	print_smaller(root->left, value);
	print_smaller(root->right, value);
}
int get_one_child_node(TreeNode *root) {
	int n = 0;
	if (root == NULL)
		return NULL;
	if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
		n++;
	n = n + get_one_child_node(root->left) + get_one_child_node(root->right);
	return n;
}
void main() {
	TreeNode *root = NULL;
	FILE *fp;
	fp = fopen("data.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int temp;
	while (!feof(fp)) {
		fscanf(fp, "%d ", &temp);
		insert_node(&root, temp);
	}
	int n = get_one_child_node(root);
	if (isBalanced(root) == 1)
		printf("균형 트리 입니다\n");
	else
		printf("균형 트리가 아닙니다\n");

	printf("노드의 합은 %d 입니다.", get_sum_node(root));

	int x;
	printf("값을 입력하시오 : ");
	scanf("%d", &x);
	print_smaller(root, x);

	printf("자식이 하나만 있는 노드의 개수 %d\n", n);
	
	inorder(root);
}