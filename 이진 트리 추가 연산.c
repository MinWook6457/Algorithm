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
int get_node_count(TreeNode *node) { // 노드의 개수 구하는 함수
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
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
int get_nonleaf_count(TreeNode *node) { // 비단말 노드의 개수 구하는 함수
	int count = 0;
	if (node != NULL) {
		if (node->left != NULL && node->right != NULL)
			count = 1 + get_nonleaf_count(node->left) + get_nonleaf_count(node->right);
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
	printf("노드의 개수 : %d \n",get_node_count(exp));
	printf("단말 노드의 개수 : %d \n", get_leaf_count(exp));
	printf("비단말 노드의 개수 : %d \n", get_nonleaf_count(exp));
	printf("노드의 높이 : %d\n", get_height(exp));
	if (equal(exp, exp))
		printf("같은 트리 입니다.\n");
	else
		printf("다른 트리 입니다.\n");
}