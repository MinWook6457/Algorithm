#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#pragma warning(disable:4996)

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
void get_degree(GraphType *g) {
	int count = 1;
	for (int i = 0; i < g->n; i++) {
		count = 0;
		for (int j = 0; j < g->n; j++) {
			if (g->adj_mat[i][j] == 1)
				count++;
		}
		printf("정점 %d의 차수는 %d\n", i, count);
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
		fprintf(stderr, "파일 열기 실패\n");
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

