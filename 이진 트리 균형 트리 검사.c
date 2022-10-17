#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

int get_height(TreeNode *node) { // ����� ���� ���ϴ� �Լ�
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
	printf("���� ����Ʈ�� ���� : %d ������ ����Ʈ�� ���� : %d \n", left_h, right_h);
	int h = abs(left_h - right_h); // ������ ���� �� �����Ƿ� ���밪
	if (h <= 1) // ����Ʈ�� �� ���̰� �ִ� 1
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
		printf("%d���� ���� ���: %d\n", value, root->data);
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
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	int temp;
	while (!feof(fp)) {
		fscanf(fp, "%d ", &temp);
		insert_node(&root, temp);
	}
	int n = get_one_child_node(root);
	if (isBalanced(root) == 1)
		printf("���� Ʈ�� �Դϴ�\n");
	else
		printf("���� Ʈ���� �ƴմϴ�\n");

	printf("����� ���� %d �Դϴ�.", get_sum_node(root));

	int x;
	printf("���� �Է��Ͻÿ� : ");
	scanf("%d", &x);
	print_smaller(root, x);

	printf("�ڽ��� �ϳ��� �ִ� ����� ���� %d\n", n);
	
	inorder(root);
}