#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 50
#pragma warning(disable:4996)

int visited[MAX_VERTICES];
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

void dfs_mat(GraphType *g, int v) {
	visited[v] = true;
	printf("���� %d -> ", v);
	for (int w = 0; w < g->n; w++) {
		if (g->adj_mat[v][w] && !visited[w])
			dfs_mat(g, w);
	}
}

int main() {
	GraphType *g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	FILE *fp;
	fp = fopen("adj.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	for (int i = 0; i < 5; i++) {
		insert_vertex(g, i);
	}

	int x, y;
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		insert_edge(g, x, y);
	}

	printf("���� �켱 Ž��\n");
	dfs_mat(g, 0);
	free(g);
	fclose(fp);

	return 0;
}

