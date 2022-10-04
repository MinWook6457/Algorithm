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
	// char animal[100];
}element;
// 왼쪽 노드 = 부모인덱스 * 2
// 오른쪽 노드 = 부모인덱스 * 2 + 1
// 부모노드 = 자식인덱스 / 2
typedef struct {
	element heap[100];
	int heap_size;
}HeapType;
HeapType *create() {
	return (HeapType *)malloc(sizeof(HeapType));
}
void init(HeapType *h) {
	h->heap_size = 0;
}
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
element max_heap_delete(HeapType *h) {
	int parent, child;
	element temp, item;

	item = h->heap[1]; // 루트값 반환을 위한 저장
	temp = h->heap[(h->heap_size)--]; // 말단 노드 저장
	parent = 1; // 부모노드 인덱스 초기값 설정
	child = 2; // 자식노드 인덱스 초기값 설정

	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중에서 더 큰 자식노드를 찾는다. (부모 기준 왼,오 검사)
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;
		}
		if (temp.key >= h->heap[child].key) { // 삭제할 값이 가장 큰 값이거나 가장 말단으로 히프 트리가 내려간 경우 while문 종료
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // 루트값 반환
}
void heap_sort(element a[],int n) {
	int i;
	HeapType *h;

	h = create();
	init(h);

	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		a[i] = max_heap_delete(h);
	}
	free(h);
}/*
void display(HeapType *h) {
	for (int i = 1; i < h->heap_size + 1; i++) {
		printf("%d : %s -> ", h->heap[i].key, h->heap[i].animal);
	}
	printf("\n");
}
*/
void main() {
	/*
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

	max_heap_delete(&heap);
	display(&heap);
	*/
	element list[8]= { 23,56,11,9,56,99,27,34 };
	heap_sort(list, 8);
	for (int i = 0; i < 8 ; i++) {
		printf("%d ", list[i].key);
	}
}