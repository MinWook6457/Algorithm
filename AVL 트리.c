#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100
#pragma warning(disable:4996)
//AVL 트리 노드 정의
typedef struct AVLNode {
	int key;
	struct AVLNode *left;
	struct AVLNode *right;
}AVLNode;

// 트리 높이 반환
int get_height(AVLNode *node) {
	int height = 0;
	if (node != NULL) {
		height = 1 + max(get_height(node->left), get_height(node->right));
	}

	return height;
}

// 노드의 균형인수 반환
int get_balance(AVLNode *node) {
	if (node == NULL)
		return 0;

	return get_height(node->left) - get_height(node->right);
}

// 노드를 동적으로 생성하는 함수
AVLNode *create_node(int key) {
	AVLNode *node = (AVLNode *)malloc(sizeof(AVLNode));
	node->key = key;
	node->left = node->right = NULL;

	return node;
}

// 오른쪽으로 회전 시키는 함수 : 왼쪽, 왼쪽으로 편향된 경우
//			C  (parent)
//		  ↙
//		B (child)
//	  ↙
//   A

AVLNode *rotate_right(AVLNode *parent) {
	AVLNode *child = parent->left;
	parent->left = child->right;
	child->right = parent;

	return child; // 새로운 루트 반환
}

// 왼쪽으로 회전 시키는 함수 : 오른쪽, 오른쪽으로 편향된 경우
//			C (parent)
//			  ↘
//				B (child)
//				  ↘
//					 A

AVLNode *rotate_left(AVLNode *parent) {
	AVLNode *child = parent->right;
	parent->right = child->left;
	child->left = parent;

	return child;
}

/*
   AVL 트리에 새로운 노드 추가 함수
   새로운 루트 노드 반환
*/

AVLNode *insert(AVLNode *node, int key) {
	// 이진 탐색 트리 노드 추가 수행
	if (node == NULL)
		return create_node(key);

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else
		return node;

	int balance = get_balance(node); // 균형인수 계산

	// LL 타입 처리
	if (balance > 1 && key < node->left->key)
		return rotate_right(node);

	// RR 타입 처리
	if (balance < -1 && key > node->right->key)
		return rotate_left(node);

	// LR 타입 처리
	if (balance > 1 && key > node->left->key) {
		node->left = rotate_left(node->left);
		return rotate_right(node);
	}

	// RL 타입 처리
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
		printf("큐가 포화상태 입니다.\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = value;
}

element dequeue(QueueType* q) {
	if (is_empty(q))
		printf("큐가 공백상태 입니다.\n");
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

