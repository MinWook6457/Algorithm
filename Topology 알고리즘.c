#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#pragma warning(disable:4996)
#define MAX_VERTICES 100

typedef struct GraphNode {
	int vertex;
	struct GraphNode* link;
}GraphNode;

typedef struct GraphType {
	int n;
	GraphNode* adj_list[MAX_VERTICES];
}GraphType;

typedef struct {
	int data[MAX_VERTICES];
	int top;
}StackType;

void graph_init(GraphType* g) {
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v] = NULL;
	}
}

void insert_vertex(GraphType* g, int v) {
	if ((g->n) + 1 > MAX_VERTICES) {
		printf("vertex overflow\n");
	}
	g->n++;
}

void insert_edge(GraphType* g, int u, int v) {
	GraphNode* node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		exit(1);
	}
	node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}


void init_stack(StackType* s) {
	s->top = -1;
}

//스택 공백 검출 함수
int is_empty(StackType* s) {
	if (s->top == -1) {
		return 1;
	}
	else
		return 0;
}
//스택 포화 검출 함수
int is_full(StackType* s) {
	if (s->top == (MAX_VERTICES - 1))
		return 1;
	else
		return 0;
}
//스택 삽입 함수
void push(StackType* s, int item) {
	if (is_full(s)) {
		return;
	}
	s->data[++(s->top)] = item;
}
//스택 삭제 함수
int pop(StackType* s) {
	if (is_empty(s)) {
		fprintf(stderr, "Empty Error\n");
		exit(1);
	}
	else
		return s->data[(s->top)--];
}


int topo_sort(GraphType* g) {
	int i;
	StackType s;
	GraphNode* node;

	int* in_degree = (int *)malloc(sizeof(g->n * sizeof(int)));
	if (in_degree == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	for (i = 0; i < g->n; i++)
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++) {
		GraphNode* node = g->adj_list[i];
		while (node != NULL) {
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	init_stack(&s);
	for (i = 0; i < g->n; i++) {
		if (in_degree[i] == 0)
			push(&s, i);
	}

	while (!is_empty(&s)) {
		int w;
		w = pop(&s);
		printf("정점 -> %d ", w);
		node = g->adj_list[w];

		while (node != NULL) {
			int u = node->vertex;
			in_degree[u]--;

			if (in_degree[u] == 0) {
				push(&s, u);
			}
			node = node->link;
		}
	}
	// free(in_degree); <- 메모리 해제시 오류 발생하여 주석 처리한 상태임. 
	printf("\n");
	return (i == g->n);
}

void main() {
	GraphType g;
	FILE* fp;

	char flag;
	int v, e1, e2;
	int count = 0;
	fp = fopen("Topo.txt", "r");

	graph_init(&g);

	while (!feof(fp)) {
		fscanf(fp, "%c", &flag);

		if (flag == 'v') {
			fscanf(fp, "%d", &v);
			insert_vertex(&g, v);
		}
		else if (flag == 'e') {
			fscanf(fp, "%d %d", &e1, &e2);
			insert_edge(&g, e1, e2);
		}
	}

	topo_sort(&g);
}

