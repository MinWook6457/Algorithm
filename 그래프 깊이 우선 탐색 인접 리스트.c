#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_VERTICES 50
#pragma warning(disable:4996)

int visited[MAX_VERTICES];
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

void dfs_list(GraphType *g, int v) {
	GraphNode *w;
	visited[v] = true;
	printf("���� : %d -> ", v);
	for (w = g->adj_list[v]; w; w = w->link) {
		if (!visited[w->vertex])
			dfs_list(g, w->vertex);
	}
}

void main() {
	GraphType *g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	FILE *fp;
	fp = fopen("adj_list.txt", "r");
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
	dfs_list(g,0);
	fclose(fp);
	free(g);

}

