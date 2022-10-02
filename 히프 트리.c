#include <stdio.h>
#include <stdlib.h>
// 히프의 특성
// 완전이진트리
// 중복데이터 허용
// 최대 혹은 최소 히프 구성
// uphead , downheap
#pragma warning(disable:4996)

typedef struct {
	int key;
	char animal[100];
}element;
// 왼쪽 노드 = 부모인덱스 * 2
// 오른쪽 노드 = 부모인덱스 * 2 + 1
// 부모노드 = 자식인덱스 / 2
typedef struct {
	element heap[100];
	int heap_size;
}HeapType;

void insert_max_heap(HeapType *h, element data) {
	int i; // heap index for new node
	// heap size increment
	i = ++(h->heap_size);

	//i가 루트가 아니고 i번째 노드가 부모 노드보다 크면
	while ((i != 1) && data.key > h->heap[i / 2].key) {
		// 자리바꿈
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = data;
}
void display(HeapType *h) {
	for (int i = 1; i < h->heap_size + 1; i++) {
		printf("%d : %s -> ", h->heap[i].key, h->heap[i].animal);
	}
	printf("\n");
}
void main() {
	FILE *fp;
	fp = fopen("data5.txt", "r");
	element tmp;
	HeapType heap;
	heap.heap_size = 0;
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	while (!feof(fp)) {
		fscanf(fp, "%d %s", &tmp.key, &tmp.animal);
		printf("%d %s\n", tmp.key, tmp.animal);
		insert_max_heap(&heap, tmp);
	}
	display(&heap);
}