#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)

#define MAX_VERTICES 100
#define INF 1000L

typedef struct GraphType {
	int n;
	int weight[MAX_VERTICES][MAX_VERTICES];
}GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

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

// 최소 dist[v] 값을 갖는 정점 반환
int get_min_vertex(int n) {
	int v, i;
	for (i = 0;i < n;i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}
	for (i = 0; i < n; i++) {
		if (!selected[i] && (distance[i] < distance[v]))
			v = i;
	}

	return (v);
}

void prim(GraphType *g, int s) {
	int i, u, v;

	for (u = 0; u < g->n; u++) {
		distance[u] = INF;
	}
	distance[s] = 0;

	for (i = 0; i < g->n; i++) {
		u = get_min_vertex(g->n);
		selected[u] = true;
		if (distance[u] == INF)
			return;
		printf("정점 %d 방문\n", u);
		for (v = 0; v < g->n; v++) {
			if (g->weight[u][v] != INF) {
				if (!selected[v] && g->weight[u][v] < distance[v])
					distance[v] = g->weight[u][v];
			}
		}
	}
}

void main() {
	FILE* fp;
	int max = 0;
	int temp1, temp2, temp3;
	fp = fopen("prim.txt", "r");
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

	for (int i = 0; i < max + 1 ; i++) {
		insert_vertex(g, i);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		insert_edge(g, temp1, temp2, temp3);
	}

	prim(g, 0);
}