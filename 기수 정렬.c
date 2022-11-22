#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100
#define BUCKETS 10
#define DIGITS 4
#define MAX_SIZE 10
typedef int element;

typedef struct QueueType{
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType *q) {
	q->rear = q->front = 0;
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType *q) {
	return (q->rear == q->front);
}

void enqueue(QueueType *q,element item) {
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태 입니다\n");
		exit(1);
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태 입니다\n");
		exit(1);
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->data[q->front];
}

void radix_sort(element list[], int n) {
	int factor = 1;
	QueueType q[BUCKETS];
	int i, b, d;
	for (b = 0; b < BUCKETS ; b++) {
		init_queue(&q[b]); // 큐초기화
	}

	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) {
			enqueue(&q[(list[i] / factor) % 10], list[i]);
		}


		for (b = i = 0; b < BUCKETS; b++) {
			while (!is_empty(&q[b])) {
				list[i++] = dequeue(&q[b]);
			}
		}
		factor *= 10;
	}


}

void main() {
	int list[MAX_SIZE];
	srand(time(NULL));

	for (int i = 0; i < MAX_SIZE; i++) {
		list[i] = rand() % 100;
	}

	radix_sort(list, MAX_SIZE);
	for (int i = 0; i < MAX_SIZE; i++) {
		printf("%d ", list[i]);
	}
}