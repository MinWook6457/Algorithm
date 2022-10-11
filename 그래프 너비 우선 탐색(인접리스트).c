#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100
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

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType {
	int n; // ������ ����
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType *g) {
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType *g, int vertex) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "�׷��� : ���� ��ȣ ����\n");
		exit(1);
	}

	g->n++;
}

void insert_edge(GraphType *g, int u, int v) { // ���� u�� ���� (u,v) ����

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷��� : ���� ���� ����\n");
		exit(1);
	}

	GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u]; // ���Ḯ��Ʈ �迭 ���� ������ ����� ������ ������ 
	g->adj_list[u] = node; // �ʿ��� ���Ḯ��Ʈ �� �տ� ����
}

void bfs_list(GraphType *g, int v) {
	GraphNode *w;
	QueueType q;

	init(&q);
	visited[v] = true; //���� v �湮 ǥ��
	printf("%d �湮 -> ", v);
	enqueue(&q, v); // ���� ���� ť�� ����

	while (!is_empty(&q)) {
		v = dequeue(&q); // ť�� ����� ���� ����
		for (w = g->adj_list[v];w;w = w->link) { // ���� ���� ����
			if (!visited[w->vertex]) { // �̹湮 ���� ǥ��
				visited[w->vertex] = true; // �湮 ǥ��
				printf("%d �湮 -> ", w->vertex);
				enqueue(&q, w->vertex); // ���� ť�� ����
			}
		}
	}
}

void main() {
	GraphType *g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	FILE *fp;
	fp = fopen("bfs.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	for (int i = 0; i < 6; i++) {
		insert_vertex(g, i);
	}

	int x, y;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		insert_edge(g, x, y);
	}

	bfs_list(g, 0);
	fclose(fp);
	free(g);

}

