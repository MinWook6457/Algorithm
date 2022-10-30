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

typedef struct {
	int key, u, v;
}element;

typedef struct {
	element heap[MAX_VERTICES];
	int heap_size;
}HeapType;

void init_heap(HeapType* h) {
	h->heap_size = 0;
}

int is_empty(HeapType* h) {
	if (h->heap_size == 0)
		return 1;
	else
		return 0;
}

void insert_min_heap(HeapType* h, element item) {
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType* h) {
	int parent, child;
	element temp, item;

	item = h->heap[1]; // ��Ʈ�� ��ȯ�� ���� ����
	temp = h->heap[(h->heap_size)--]; // ���� ��� ����
	parent = 1; // �θ��� �ε��� �ʱⰪ ����
	child = 2; // �ڽĳ�� �ε��� �ʱⰪ ����

	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �߿��� �� ū �ڽĳ�带 ã�´�. (�θ� ���� ��,�� �˻�)
		if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key)) {
			child++;
		}
		if (temp.key <= h->heap[child].key) { // ���� ��尡 child ���� �� ������ ������ �� ����
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // ��Ʈ�� ��ȯ
}

void insert_all_edge(HeapType* h) {
	int temp1, temp2, temp3;
	element e;
	FILE* fp2;
	fp2 = fopen("kruskal.txt", "r");

	if (fp2 == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	while (!feof(fp2)) {
		fscanf(fp2, "%d %d %d", &temp1, &temp2, &temp3);
		e.u = temp1;
		e.v = temp2;
		e.key = temp3;
		insert_min_heap(h, e);
	}
	fclose(fp2);
}

void kruskal(int n) {
	HeapType h;
	element e;
	int edge_accepted = 0;
	int uset, vset;
	init_heap(&h);

	insert_all_edge(&h); // ��Ʈ���� ������������ ���� ����
	set_init(n);

	while (edge_accepted < (n - 1)) {
		e = delete_min_heap(&h);
		uset = set_find(e.u);
		vset = set_find(e.v);

		if (uset != vset) { // none cycle : success
			printf("(%d %d) %d\n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset);
		}
	}
}

void main() {
	FILE* fp;
	int max = 0;
	int temp1, temp2, temp3;
	element g[MAX_VERTICES];
	fp = fopen("kruskal.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	int count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d %d %d", &temp1, &temp2, &temp3);
		if (temp2 > max)
			max = temp2;
	}
	kruskal(max + 1);
}