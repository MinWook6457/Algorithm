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

int count; // 출력을 위한 전역변수

void graph_init(GraphType* g) {
	g->n = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (i == j)
				g->weight[i][j] = 0;
			else
				g->weight[i][j] = INF;
		}
	}
}

void insert_vertex(GraphType* g, int n) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점 삽입 오류\n");
		exit(1);
	}
	g->n++;
}

void insert_edge(GraphType* g, int start, int end, int weight) {
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프 간선 삽입 오류\n");
		exit(1);
	}

	g->weight[start][end] = weight;
	g->weight[end][start] = weight;
}

void PrintF(GraphType *g) {
	if (count == 0) {
		printf("-1상태\n");
		count++;
	}
	else {
		printf("0부터 %d 까지의 모든 정점을 이용한 최단거리 \n", count - 1);
		count++;
	}
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			if (g->weight[i][j] == INF)
				printf("INF\t");
			else
				printf("%d\t", g->weight[i][j]);
		}
		printf("\n");
	}
	printf("==========================================================\n\n\n");

}

void floyd(GraphType *g) {
	int i, j, k;
	for (k = 0; k < g->n; k++) {
		for (i = 0; i < g->n; i++) {
			for (j = 0; j < g->n; j++) {
				if (g->weight[i][k] + g->weight[k][j] < g->weight[i][j]) {
					g->weight[i][j] = g->weight[i][k] + g->weight[k][j];
				}
			}
		}
		PrintF(g);
	}
}


void main() {
	FILE* fp;
	int max = 0;
	int temp1, temp2, temp3;
	fp = fopen("Floyd.txt", "r");
	GraphType* g;
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (temp2 > max)
			max = temp2;
	}
	rewind(fp);
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	for (int i = 0; i < max + 1; i++) {
		insert_vertex(g, i);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		insert_edge(g, temp1, temp2, temp3);
	}
	PrintF(g);
	floyd(g);
	fclose(fp);
}