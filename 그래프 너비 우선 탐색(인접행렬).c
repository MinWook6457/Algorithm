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
		fprintf(stderr, "큐가 포화상태 입니다.\n");
		return;
	}

	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

element dequeue(QueueType *q) {
	if (is_empty(q)) {
		fprintf(stderr, "큐가 공백상태입니다\n");
		return;
	}

	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


typedef struct GraphType {
	int n; // 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; // 행렬 선언
}GraphType;

//그래프 초기화
void init(GraphType *g) {
	int r, c; // r : 행 c : 열
	g->n = 0;

	for (r = 0; r < MAX_VERTICES; r++) {
		for (c = 0;c < MAX_VERTICES;c++) {
			g->adj_mat[r][c] = 0;
		}
	}
}

//정점 삽입 연산
void insert_vertex(GraphType *g, int vertex) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		exit(1);
	}
	g->n++;
}

//간선 삽입 연산
void insert_edge(GraphType *g, int start, int end) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 : 간선 오류\n");
		exit(1);
	}

	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1; // 방향 그래프의 경우 g->adj_mat[end][start] = 0
}

void bfs_mat(GraphType *g, int v) {
	int w;
	QueueType q;
	init_queue(&q);

	visited[v] = true;
	printf("%d 방문 -> ", v);
	enqueue(&q, v);
	while (!is_empty(&q)) {
		v = dequeue(&q);
		for (w = 0;w < g->n;w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				visited[w] = true;
				printf("%d 방문 -> ", w);
				enqueue(&q, w);
			}
		}
	}
}

void main() {
	FILE *fp;
	fp = fopen("bfs.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
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

	printf("너비 우선 탐색\n");
	bfs_mat(g, 0);

	free(g);
	fclose(fp);
}