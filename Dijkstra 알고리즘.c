#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define MAX_VERTICES 100
#define INF 1000000

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES]; // 방문한 정점 표시

void graph_init(GraphType *g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			g->weight[i][j] = INF;
		}
	}
}

void insert_vertex(GraphType *g, int n) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점 삽입 오류\n");
		exit(1);
	}
	g->n++;
}

void insert_edge(GraphType *g, int start, int end, int weight) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 간선 삽입 오류\n");
		exit(1);
	}

	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}

int choose(int distance[], int n, int found[]) {
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;

	for (i = 0; i < n; i++) {
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void print_status(GraphType *g) {
	static int step = 1;
	printf("STEP %d : ", step++);
	printf("distance : ");
	for (int i = 0; i < g->n; i++) {
		if (distance[i] == INF)
			printf(" * ");
		else
			printf("%2d ", distance[i]);
	}

	printf("\n");
	printf("found : ");
	for (int i = 0; i < g->n; i++) {
		printf("%2d ", found[i]);
	}
	printf("\n\n");
}

void shortest_Path(GraphType *g, int start) {
	int i, u, w;

	for (i = 0;i < g->n;i++) {
		distance[i] = g->weight[start][i];
		found[i] = false; 
	}

	found[start] = true;
	distance[start] = 0;

	for (i = 0;i < g->n - 1;i++) {
		print_status(g);
		u = choose(distance, g->n, found);
		found[u] = true;
		for (w = 0;w < g->n;w++) {
			if (!found[w]) {
				if (distance[u] + g->weight[u][w] < distance[w]) {
					distance[w] = distance[u] + g->weight[u][w];
				}
			}
		}
	}
}

void main() {
	FILE* fp;
	int max = 0;
	int temp1, temp2, temp3;
	fp = fopen("Dijkstra.txt", "r");
	GraphType *g;
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (temp2 > max)
			max = temp2;
	}
	rewind(fp);
	g = (GraphType *)malloc(sizeof(GraphType));
	graph_init(g);

	for (int i = 0; i < max + 1; i++) {
		insert_vertex(g, i);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		insert_edge(g, temp1, temp2, temp3);
	}

	shortest_Path(g, 0);
}

