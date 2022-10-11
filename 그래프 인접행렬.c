#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#pragma warning(disable:4996)

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
void get_degree(GraphType *g) {
	int count = 1;
	for (int i = 0; i < g->n; i++) {
		count = 0;
		for (int j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1)
				count++;
		}
		printf("���� %d�� ������ %d\n", i, count);
	}
}
void print_adj_matrix(GraphType *g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
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

	print_adj_matrix(g);
	get_degree(g);
	free(g);
	fclose(fp);

	return 0;
}

