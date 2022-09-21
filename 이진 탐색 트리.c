#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int key;
	struct TreeNode *left, *right;
}TreeNode;
// ��ȯ���� Ž�� �Լ�
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
TreeNode *min_value_node(TreeNode *node) { // �ּ� Ű ���� ������ ��带 ��ȯ
	TreeNode *current = node;

	while (current->left != NULL)
		current = current->left;

	return current;
}
TreeNode *delete_node(TreeNode *root, int key) {
	if (root == NULL)
		return root;
	if (key < root->key) // ���� Ű�� ��Ʈ���� ������ ���� ����Ʈ���� �ִٴ� ����
		root->left = delete_node(root->left, key);
	else if(key>root->key) // ���� Ű�� ��Ʈ���� ũ�ٸ� ������ ����Ʈ���� �ִٴ� ����
		root->right = delete_node(root->right, key);
	else { // Ű�� ��Ʈ�� ������ �� ��带 �����ϸ� ��
		// �����Ϸ��� ��尡 �ܸ� ����� ��� �̰ų� �����Ϸ��� ��尡 �ϳ��� ����Ʈ���� ������ �ִ°��
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

		// �����Ϸ��� ��尡 �ΰ��� ����Ʈ���� ������ �ִ� ���
		TreeNode *temp = min_value_node(root->right);

		root->key = temp->key;
		root->right = delete_node(root->right, temp->key);
	}
	return root;
}

void inorder(TreeNode* root) { // ���� ��ȸ
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
		fprintf(stderr, "���� ���� ����\n");
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
	
	printf("���� Ž�� Ʈ�� ���� ��ȸ ���\n");
	inorder(root);
	printf("\n\n");

	if (search(root, 30) != NULL)
		printf("���� Ž��Ʈ������ 30�� �߰���\n");
	else
		printf("���� Ž��Ʈ������ 30�� �߰߸���\n");
}
