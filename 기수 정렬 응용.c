#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define MAX_QUEUE_SIZE 100
#define BUCKETS 10
#define DIGITS 3
typedef int element;

typedef struct QueueType {
	element data[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init_queue(QueueType* q) {
	q->rear = q->front = 0;
}

int is_full(QueueType* q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType* q) {
	return (q->rear == q->front);
}

void enqueue(QueueType* q, element item) {
	if (is_full(q)) {
		fprintf(stderr, "큐가 포화상태 입니다\n");
		exit(1);
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
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
	for (b = 0; b < BUCKETS; b++) {
		init_queue(&q[b]); // 큐초기화
	}
	printf("\n정렬 과정\n");
	for (d = 0; d < DIGITS; d++) {
		printf("-DIGIT %d-\n", d + 1);
		for (i = 0; i < n; i++) {
			enqueue(&q[(list[i] / factor) % 10], list[i]);
		}


		for (b = i = 0; b < BUCKETS; b++) {
			printf("Bucket[%d] :", b);
			if (is_empty(&q[b])) {
				printf("Empty");
			}
			while (!is_empty(&q[b])) {
				list[i] = dequeue(&q[b]);
				printf("%d ", list[i++]);
			}
			printf("\n");
		}
		factor *= 10;
	}
}

void main() {
	FILE* fp;

	fp = fopen("bucket.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int count = 0;
	int tmp;
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		count++;
	}
	int* list = (int*)malloc(sizeof(int) * count);

	rewind(fp);

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &list[i]);
	}
	printf("정렬 전 리스트 : ");
	for (int i = 0; i < count; i++)
		printf("%d > ", list[i]);
	printf("\n");

	radix_sort(list, count);

	printf("< 정렬 후 데이터 >\n");
	for (int i = 0; i < count; i++)
		printf("%d > ", list[i]);
}