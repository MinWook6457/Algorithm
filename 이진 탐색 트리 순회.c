#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;
typedef TreeNode* element;
typedef struct QueueNode // ���Ḯ��Ʈ ť ����
{
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct Queue
{
	QueueNode* front, *rear;
}Queue;

void QueueInit(Queue* q) // ť �ʱ�ȭ
{
	q->front = q->rear = NULL;
}
// ť ���� �˻�
int	is_empty(Queue* q)
{
	return q->front == NULL;
}
// ť�� ������ ����
void enqueue(Queue* q, element data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->link = NULL;
	newNode->data = data;
	if (is_empty(q)) {
		q->front = newNode;
		q->rear = newNode;
	}
	else {
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

// ť���� ������ ����
void dequeue(Queue* q)
{
	QueueNode* pDelNode = q->front;
	q->front = q->front->link;	//	front�� ���� ��ġ�� �̵� : ���Ḯ��Ʈ �̿�
	free(pDelNode);
}
// ť�� �ִ� ��� ������ ����
void DeleteAllNode(Queue* q)
{
	while (!is_empty(q))
		dequeue(q);
}
// ������ȸ
void LevelTraversal(TreeNode* pRoot)
{
	Queue q;
	TreeNode* p = NULL;

	QueueInit(&q);		// ť�� �ʱ�ȭ
	enqueue(&q, pRoot);	// ��Ʈ ��带 ť�� ����
	while (!QueueIsEmpty(&q))
	{
		p = q.front->data;	// ��� p�� q�� ������ �ִ� �����͸� ����Ŵ
		printf("%d ", p->data);
		if (p->left != NULL)
			enqueue(&q, p->left);
		if (p->right != NULL)
			enqueue(&q, p->right);

		dequeue(&q); // ť���� ���� ��带 ����
	}
	DeleteAllNode(&q);
}

TreeNode *newNode(int item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
// ������� ����
TreeNode *insert_node_recurcive(TreeNode *node, int key) {
	if (node == NULL)
		return newNode(key);
	if (key < node->data)
		node->left = insert_node_recurcive(node->left, key);
	else
		node->right = insert_node_recurcive(node->right, key);
	return node;
}
// �ݺ����� ����
void insert_node(TreeNode **root, int item) {
	TreeNode* p, *t; // p�� t�� �θ��� t�� ������ġ

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (item == t->data) // ���� �߰��Ϸ��� �ܾ �̹� Ʈ���� �ִ� ���
			return;
		p = t; // *** �θ� ��� ������Ʈ ***
		if (item < t->data)
			t = t->left;
		else
			t = t->right;
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	n->data = item;
	//printf("%d ", n->data);
	n->left = n->right = NULL;

	if (p != NULL) {
		if (item < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else {
		*root = n;
	}
}
void preorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		printf("[%d] ", temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}
void inorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		inorder(temp->left);
		printf("[%d] ", temp->data);
		inorder(temp->right);
	}
}
void postorder(TreeNode* temp) { // ���� ��ȸ
	if (temp != NULL) {
		postorder(temp->left);
		postorder(temp->right);
		printf("[%d] ", temp->data);
	}
}
int get_height(TreeNode *node) { // ����� ���� ���ϴ� �Լ�
	if (node == NULL) {
		return 0;
	}
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	return left_height > right_height ? left_height + 1 : right_height + 1;
}
void *delete_node(TreeNode *root) {//�������� �Ҵ�� ������ �޸𸮸� ��ȯ�ϴ� �Լ�
	if (root != NULL) {
		delete_node(root->left);
		delete_node(root->right);
		free(root);
	}
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
int get_node_count(TreeNode *node) { // ����� ���� ���ϴ� �Լ�
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}
void main() {
	clock_t start1, end1; // �ݺ� �ð� ������ ���� ����
	clock_t start2, end2; // ��ȯ �ð� ������ ���� ����
	clock_t start3, end3; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start4, end4; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start5, end5; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start6, end6; // ���� ��ȸ �ð� ������ ���� ����
	FILE *fp;
	TreeNode *root1 = NULL;
	TreeNode *root2 = NULL;
	fp = fopen("data.txt", "r");
	int tmp;
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	start1 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		insert_node(&root1, tmp);
	}
	end1 = clock();
	printf("\n[���Կ��� �ݺ������ �ɸ��ð� : %f]\n", (float)(end1 - start1) / CLOCKS_PER_SEC);
	int h1 = get_height(root1);
	printf("Height = %d\n", h1);

	rewind(fp);
	
	start2 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		root2 = insert_node_recurcive(root2, tmp);
	}
	end2 = clock();
	printf("\n[���Կ��� ��ȸ����� �ɸ��ð� : %f]\n", (float)(end2 - start2) / CLOCKS_PER_SEC);
	printf("\n");
	printf("Ʈ���� ���� = %d, �ܸ� ��� ���� = %d ��� ��� ���� = %d ", get_height(root1), get_leaf_count(root1), get_node_count(root1));
	

	/*
	start3 = clock();
	preorder(root1);
	end3 = clock();
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end3 - start3) / CLOCKS_PER_SEC);
	*/

	/*
	start4 = clock();
	inorder(root1);
	end4 = clock();
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end4 - start4) / CLOCKS_PER_SEC);
	*/

	/*
	start5 = clock();
	postorder(root1);
	end5 = clock();
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end5 - start5) / CLOCKS_PER_SEC);

	*/
	start6 = clock();
	LevelTraversal(root1);
	end6 = clock();
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end6 - start6) / CLOCKS_PER_SEC);
	delete_node(root1); // Ʈ�� ��� ����
	delete_node(root2); // Ʈ�� ��� ����
	fclose(fp);
}