#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <malloc.h>
#define MAX_QUEUE_SIZE 100
typedef struct TreeNode {
	int data;
	struct TreeNode* L, *R;
}TreeNode;
typedef TreeNode* element;

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

void level_order(TreeNode* ptr) {
	QueueType q;
	init(&q);

	if (ptr == NULL)
		return;

	enqueue(&q, ptr);
	while (!is_empty(&q)) {
		ptr = dequeue(&q);
		printf("[%d] ", ptr->data);
		if (ptr->L != NULL)
			enqueue(&q, ptr->L);
		if (ptr->R != NULL) {
			enqueue(&q, ptr->R);
		}
	}
}

void main() {
	TreeNode* n1 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n2 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n3 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n4 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n5 = (TreeNode*)malloc(sizeof(TreeNode));
	TreeNode* n6 = (TreeNode*)malloc(sizeof(TreeNode));

	n6->data = 15;
	n6->L = n2;
	n6->R = n5;

	n2->data = 4;
	n2->L = n1;
	n2->R = NULL;

	n1->data = 1;
	n1->L = NULL;
	n1->R = NULL;

	n5->data = 20;
	n5->L = n3;
	n5->R = n4;

	n3->data = 16;
	n3->L = NULL;
	n3->R = NULL;

	n4->data = 25;
	n4->L = NULL;
	n4->R = NULL;

	printf("레벨 순회 : ");
	level_order(n6);
	printf("\n20194024 김민욱");
}
