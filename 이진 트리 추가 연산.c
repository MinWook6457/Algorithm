#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,NULL,NULL };
TreeNode n3 = { '*',&n1,&n2 };
TreeNode n4 = { 16, NULL , NULL };
TreeNode n5 = { 25, NULL , NULL };
TreeNode n6 = { '+',&n4, &n5 };
TreeNode n7 = { '+',&n3, &n6 };
TreeNode *exp = &n7;
int get_node_count(TreeNode *node) { // ����� ���� ���ϴ� �Լ�
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
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
int get_nonleaf_count(TreeNode *node) { // ��ܸ� ����� ���� ���ϴ� �Լ�
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL)
			count = 1 + get_nonleaf_count(node->left) + get_nonleaf_count(node->right);
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
bool equal(TreeNode *t1, TreeNode *t2) {
	if (t1&&t2)
		return true;
	else {
		if (t1->data == t2->data) {
			if (!equal(t1->left, t2->left))
				return false;
			if (!equal(t1->right, t2->right))
				return false;
			return true;
		}
		return false;
	}
	return false;
}
void main() {
	printf("����� ���� : %d \n",get_node_count(exp));
	printf("�ܸ� ����� ���� : %d \n", get_leaf_count(exp));
	printf("��ܸ� ����� ���� : %d \n", get_nonleaf_count(exp));
	printf("����� ���� : %d\n", get_height(exp));
	if (equal(exp, exp))
		printf("���� Ʈ�� �Դϴ�.\n");
	else
		printf("�ٸ� Ʈ�� �Դϴ�.\n");
}