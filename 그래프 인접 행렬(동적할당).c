#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct GraphType {
	int n; // ������ ����
	int **adj_mat; // ��� ����
}GraphType;

//�׷��� �ʱ�ȭ
void init(GraphType *g,int n) {
	g->n = 0;
	g->adj_mat = (int **)malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++) {
		g->adj_mat[i] = (int *)malloc(sizeof(int)*n);
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g->adj_mat[i][j] = 0;
		}
	}
}

//���� ���� ����
void insert_vertex(GraphType *g, int vertex, int matrix) {
	if ((g->n) + 1 > matrix) {
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
	int x, y;
	int count = 0;

	FILE *fp;
	fp = fopen("adj.txt", "r");
	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		count++;
	}
	init(g, 5);

	for (int i = 0; i < 5; i++) {
		insert_vertex(g, i, count);
	}

	rewind(fp);
	while (!feof(fp)) {
		fscanf(fp, "%d %d", &x, &y);
		insert_edge(g, x, y);
	}

	print_adj_matrix(g);
	get_degree(g);
	
	fclose(fp);
	return 0;
}

