#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define MAX_TERM 100
#define MAX_VERTICES 50
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
typedef struct {
	int data[MAX_TERM];
	int top;
}StackType;

void init_stack(StackType *s) {
	s->top = -1;
}

//���� ���� ���� �Լ�
int is_empty(StackType *s) {
	if (s->top == -1) {
		return 1;
	}
	else
		return 0;
}
//���� ��ȭ ���� �Լ�
int is_full(StackType *s) {
	if (s->top == (MAX_TERM - 1))
		return 1;
	else
		return 0;
}
//���� ���� �Լ�
void push(StackType *s, int item) {
	if (is_full(s)) {
		return 0;
	}
	s->top++;
	s->data[s->top] = item;
}
//���� ���� �Լ�
int pop(StackType *s) {
	if (is_empty(s)) {
		fprintf(stderr, "Empty Error\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}

void dfs_interative(GraphType *g, int v) {
	StackType *s = (StackType*)malloc(sizeof(StackType));
	init_stack(s);
	for (int i = 0; i < MAX_VERTICES; i++) {
		visited[i] = false;
	}
	visited[v] = true;
	push(s, v);
	int temp;
	while (!is_empty(s)) {
		for (int w = 0; w < g->n; w++) {
			if (g->adj_mat[v][w] && !visited[w]) {
				push(s, v);
				visited[w] = true;
				v = w;
			}
			else {
				v = pop(s);
			}
		}
	}
}

void print_adj(GraphType *g) {
	for (int i = 0; i < g->n; i++) {
		for (int j = 0; j < g->n; j++) {
			printf("%2d ", g->adj_mat[i][j]);
		}
		printf("\n");
	}
}

void main() {
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
	dfs_interative(g, 0);
	print_adj(g);
	

	free(g);
	fclose(fp);
}