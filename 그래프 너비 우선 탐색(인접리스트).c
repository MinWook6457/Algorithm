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

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
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
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		exit(1);
	}

	g->n++;
}

void insert_edge(GraphType *g, int u, int v) { // 정점 u에 간선 (u,v) 삽입

	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 간선 삽입 오류\n");
		exit(1);
	}

	GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u]; // 연결리스트 배열 마다 각각의 헤더를 가지고 있으며 
	g->adj_list[u] = node; // 필요한 연결리스트 맨 앞에 삽입
}

void bfs_list(GraphType *g, int v) {
	GraphNode *w;
	QueueType q;

	init(&q);
	visited[v] = true; //정점 v 방문 표시
	printf("%d 방문 -> ", v);
	enqueue(&q, v); // 시작 지점 큐에 저장

	while (!is_empty(&q)) {
		v = dequeue(&q); // 큐에 저장된 정점 선택
		for (w = g->adj_list[v];w;w = w->link) { // 인접 정점 선택
			if (!visited[w->vertex]) { // 미방문 정점 표시
				visited[w->vertex] = true; // 방문 표시
				printf("%d 방문 -> ", w->vertex);
				enqueue(&q, w->vertex); // 정점 큐에 삽입
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
		fprintf(stderr, "파일 열기 실패\n");
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

