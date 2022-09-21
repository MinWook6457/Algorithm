#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
}TreeNode;
// 순환적인 탐색 함수
TreeNode *search(TreeNode *node, int key) {
	if (node == NULL)
		return NULL;
	if (key == node->key)
		return node;
	else if (key < node->key)
		return search(node->left, key);
	else
		return search(node->right, key);
}

TreeNode *new_node(int item) {
	TreeNode *temp = (TreeNode *)malloc(sizeof(TreeNode));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}

TreeNode *insert_node(TreeNode *node, int key) {
	if (node == NULL)
		return new_node(key);
	if (key < node->key)
		node->left =  insert_node(node->left, key);
	else
		node->right = insert_node(node->right, key);

	return node;
}
TreeNode *min_value_node(TreeNode *node) { // 최소 키 값을 가지는 노드를 반환
	TreeNode *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
TreeNode *delete_node(TreeNode *root, int key) {
	if (root == NULL)
		return root;
	if (key < root->key) // 만약 키가 루트보다 작으면 왼쪽 서브트리에 있다는 것임
		root->left = delete_node(root->left, key);
	else if(key>root->key) // 만약 키가 루트보다 크다면 오른쪽 서브트리에 있다는 것임
		root->right = delete_node(root->right, key);
	else { // 키가 루트와 같으면 이 노드를 삭제하면 됨
		// 삭제하려는 노드가 단말 노드인 경우 이거나 삭제하려는 노드가 하나의 서브트리만 가지고 있는경우
		if (root->left == NULL) {
			TreeNode *temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			TreeNode *temp = root->left;
			free(root);
			return temp;
		}

		// 삭제하려는 노드가 두개의 서브트리를 가지고 있는 경우
		TreeNode *temp = min_value_node(root->right);

		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void inorder(TreeNode* root) { // 중위 순회
	if (root != NULL) {
		inorder(root->left);
		printf("[%d] ", root->key);
		inorder(root->right);
	}
}
void main() {
	TreeNode * root = NULL;
	TreeNode * tmp = NULL;
	FILE *fp = NULL;
	fp = fopen("data.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int count = 0;
	int temp;

	while (!feof(fp)) {
		fscanf(fp, "%d", &temp);
		count++;
	}
	rewind(fp);

	int *x = (int *)malloc(sizeof(int)*count);
	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &temp);
		x[i] = temp;
	}
	for (int i = 0; i < count; i++) {
		root = insert_node(root, x[i]);
	}
	fclose(fp);
	
	printf("이진 탐색 트리 중위 순회 결과\n");
	inorder(root);
	printf("\n\n");

	if (search(root, 30) != NULL)
		printf("이진 탐색트리에서 30을 발견함\n");
	else
		printf("이진 탐색트리에서 30을 발견못함\n");
}
