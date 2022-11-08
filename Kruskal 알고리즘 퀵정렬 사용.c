#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define INF 1000
#define MAX_VERTICES 100

int parent[MAX_VERTICES];
int num[MAX_VERTICES];

void set_init(int n) {
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

int set_find(int curr) {
	if (parent[curr] == -1)
		return curr;
	while (parent[curr] != -1)
		curr = parent[curr];
	return curr;
}

void set_union(int a, int b) {
	int root1 = set_find(a);
	int root2 = set_find(b);
	if (root1 != root2)
		parent[root1] = root2;
}

typedef struct Edge {
	int start, end, weight;
}Edge;

typedef struct GraphType {
	int n; // 간선의 개수
	int nVertex; // 정점의 개수
	struct Edge edges[2 * MAX_VERTICES];
}GraphType;

void graph_init(GraphType *g) {
	g->n = g->nVertex = 0;
	for (int i = 0; i < MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}

void insert_vertex(GraphType *g, int n) {
	if ((g->n) + 1 > MAX_VERTICES) {
		fprintf(stderr, "그래프 정점 삽입 오류\n");
		exit(1);
	}
	g->nVertex++;
}

void insert_edge(GraphType *g, int start, int end, int weight) {
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = weight;
	g->n++;
}

int compare(const  void *a, const void *b) {
	struct Edge *x = (struct Edge *)a;
	struct Edge *y = (struct Edge *)b;
	return (x->weight - y->weight);
}

void kruskal(GraphType *g) {
	int edge_accepted = 0; // 현재까지 선택된 간선의 수
	int uset, vset;

	struct Edge e;

	set_init(g->nVertex);

	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("크루스칼 최소 신장 트리 알고리즘 \n");
	int i = 0;
	while (edge_accepted < (g->nVertex - 1)) {
		e = g->edges[i];
		uset = set_find(e.start);
		vset = set_find(e.end);
		if (uset != vset) {
			printf("간선 (%d %d) %d 선택 \n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);
		}
		i++;
	}
	
}

void main() {
	FILE* fp;
	int max = 0;
	int temp1, temp2, temp3;
	fp = fopen("Kruskal.txt", "r");
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

	for (int i = 0; i < max + 1; i++) {
		insert_vertex(g, i);
	}

	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		insert_edge(g, temp1, temp2, temp3);
	}

	kruskal(g);
	fclose(fp);
}