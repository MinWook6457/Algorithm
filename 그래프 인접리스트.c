#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#pragma warning(disable:4996)

typedef struct GraphNode {
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType {
	int n; // 정점의 개수
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

void init(GraphType *g) {
	g->n = 0;
	for (int v = 0; v < MAX_VERTICES; v++) {
		g->adj_list[v]= NULL;
	}
}

void insert_vertex(GraphType *g,int vertex) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 : 정점 번호 오류\n");
		exit(1);
	}

	g->n++;
}

void insert_edge(GraphType *g, int u, int v) { // 정점 u에 간선 (u,v) 삽입
	
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "그래프 : 간선 삽입 오류\n");
		exit(1);
	}

	GraphNode *node = (GraphNode*)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u]; // 연결리스트 배열 마다 각각의 헤더를 가지고 있으며 
	g->adj_list[u] = node; // 필요한 연결리스트 맨 앞에 삽입
}

void print_adj_list(GraphType *g) {
	for (int i = 0; i < g->n; i++) {
		GraphNode *p = g->adj_list[i];
		printf("정점 %d의 인접 리스트 ", i);
		while (p != NULL) {
			printf("-> %d ", p->vertex);
			p = p->link;
		}
		printf("\n");
	}
}
void get_degree(GraphType *g) {
	int count = 0;
	for (int i = 0; i < g->n; i++) {
		count = 0;
		GraphNode *p = g->adj_list[i];
		while (p != NULL) {
			count++;
			p = p->link;
		}
		printf("정점 %d의 차수 : %d\n", i, count);
	}
}
void main() {
	GraphType *g = (GraphType*)malloc(sizeof(GraphType));
	init(g);

	FILE *fp;
	fp = fopen("adj_list.txt", "r");
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
	print_adj_list(g);
	get_degree(g);
	fclose(fp);
	free(g);

}

