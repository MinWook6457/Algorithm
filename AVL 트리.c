#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#pragma warning(disable:4996)
//AVL Ʈ�� ��� ����
typedef struct AVLNode {
	int key;
	struct AVLNode *left;
	struct AVLNode *right;
}AVLNode;

// Ʈ�� ���� ��ȯ
int get_height(AVLNode *node) {
	int height = 0;
	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}

	return height;
}

// ����� �����μ� ��ȯ
int get_balance(AVLNode *node) {
	if (node == NULL)
		return 0;

	return get_height(node->left) - get_height(node->right);
}

// ��带 �������� �����ϴ� �Լ�
AVLNode *create_node(int key) {
	AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = node->right = NULL;

	return node;
}

// ���������� ȸ�� ��Ű�� �Լ� : ����, �������� ����� ���
//			C  (parent)
//		  ��
//		B (child)
//	  ��
//   A

AVLNode *rotate_right(AVLNode *parent) {
	AVLNode *child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child; // ���ο� ��Ʈ ��ȯ
}

// �������� ȸ�� ��Ű�� �Լ� : ������, ���������� ����� ���
//			C (parent)
//			  ��
//				B (child)
//				  ��
//					 A

AVLNode *rotate_left(AVLNode *parent) {
	AVLNode *child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

/*
   AVL Ʈ���� ���ο� ��� �߰� �Լ�
   ���ο� ��Ʈ ��� ��ȯ
*/

AVLNode *insert(AVLNode *node, int key) {
	// ���� Ž�� Ʈ�� ��� �߰� ����
	if (node == NULL)
		return create_node(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	int balance = get_balance(node); // �����μ� ���

	// LL Ÿ�� ó��
	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	// RR Ÿ�� ó��
	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	// LR Ÿ�� ó��
	if (balance > 1 && key > node->left->key) {
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL Ÿ�� ó��
	if (balance < -1 && key < node->right->key) {
		node->right = rotate_right(node->right);
		return rotate_left(node);
	}
	return node;
}

void preorder(AVLNode *root) {
	if (root != NULL) {
		printf("[%d] ", root->key);
		preorder(root->left);
		preorder(root->right);
	}
}

typedef AVLNode* element;

typedef struct QueueType {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init(QueueType* q) {
	q->rear = q->front = 0;
}

int is_empty(QueueType* q) {
	return q->front == q->rear;
}

int is_full(QueueType* q) {
	return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType* q, element value) {
	if (is_full(q))
		printf("ť�� ��ȭ���� �Դϴ�.\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = value;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		printf("ť�� ������� �Դϴ�.\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void level_order(AVLNode* ptr) {
	QueueType q;
	init(&q);

	if (ptr == NULL)
		return;

	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("[%d] ", ptr->key);
		if (ptr->left != NULL)
			enqueue(&q, ptr->left);
		if (ptr->right != NULL) {
			enqueue(&q, ptr->right);
		}
	}
}

void main() {
	AVLNode *root = NULL;

	FILE *fp;

	fp = fopen("AVL.txt", "r");

	int tmp;
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		root = insert(root, tmp);
	}
	level_order(root);
	fclose(fp);
}

