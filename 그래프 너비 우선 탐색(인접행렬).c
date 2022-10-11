#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 100
#define MAX_VERTICES 50
#pragma warning(disable:4996)
int visited[MAX_VERTICES];
typedef int element;
typedef struct {
	int rear;
	int front;
	element queue[MAX_QUEUE_SIZE];
}QueueType;

void init_queue(QueueType *q) {
	q->front = 0;
	q->rear = 0;
}

int is_empty(QueueType *q) {
	return (q->rear == q->front);
}

int is_full(QueueType *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

void enqueue(QueueType *q, int item) {
	if (is_full(q)) {
		fprintf(stderr, "ť�� ��ȭ���� �Դϴ�.\n");
		return;
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {
		fprintf(stderr, "ť�� ��������Դϴ�\n");
		return;
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


typedef struct GraphType {
	int n; // ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // ��� ����
}GraphType;

//�׷��� �ʱ�ȭ
void init(GraphType *g) {
	int r, c; // r : �� c : ��
	g->n = 0;

	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0;c < MAX_VERTICES;c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

//���� ���� ����
void insert_vertex(GraphType *g, int vertex) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����\n");
		exit(1);
	}
	g->n++;
}

//���� ���� ����
void insert_edge(GraphType *g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷��� : ���� ����\n");
		exit(1);
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1; // ���� �׷����� ��� g->adj_mat[end][start] = 0
}

void bfs_mat(GraphType *g, int v) {
	int w;
	QueueType q;
	init_queue(&q);

	visited[v] = true;
	printf("%d �湮 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 0;w < g->n;w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = true;
				printf("%d �湮 -> ", w);
				enqueue(&q, w);
			}
		}
	}
}

void main() {
	FILE *fp;
	fp = fopen("bfs.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	GraphType *g = (GraphType *)malloc(sizeof(GraphType));
	init(g);

	for (int i = 0; i < 6; i++) {
		insert_vertex(g, i);
	}
	int x, y;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		insert_edge(g, x, y);
	}

	printf("�ʺ� �켱 Ž��\n");
	bfs_mat(g, 0);

	free(g);
	fclose(fp);
}