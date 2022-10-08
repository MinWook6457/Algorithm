#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define MAX 101

typedef struct {
	int key;
}element;

typedef struct {
	int heap[MAX];
	int heap_size;
}HeapType;

HeapType* create() {
	return (HeapType*)malloc(sizeof(HeapType));
}

void init(HeapType* h) {
	h->heap_size = 0;
}


void insert_max_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

void insert_min_heap(HeapType* h, int item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item < h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

int delete_max_heap(HeapType* h) {
	int parent, child;
	int temp, item;

	item = h->heap[1]; // 루트값 반환을 위한 저장
	temp = h->heap[(h->heap_size)--]; // 말단 노드 저장
	parent = 1; // 부모노드 인덱스 초기값 설정
	child = 2; // 자식노드 인덱스 초기값 설정

	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중에서 더 큰 자식노드를 찾는다. (부모 기준 왼,오 검사)
		if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1])) {
			child++;
		}
		if (temp >= h->heap[child]) { // 삭제할 값이 가장 큰 값이거나 가장 말단으로 히프 트리가 내려간 경우 while문 종료
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // 루트값 반환
}

int delete_min_heap(HeapType* h) {
	int parent, child;
	int temp, item;

	item = h->heap[1]; // 루트값 반환을 위한 저장
	temp = h->heap[(h->heap_size)--]; // 말단 노드 저장
	parent = 1; // 부모노드 인덱스 초기값 설정
	child = 2; // 자식노드 인덱스 초기값 설정

	while (child <= h->heap_size) {
		// 현재 노드의 자식 노드 중에서 더 큰 자식노드를 찾는다. (부모 기준 왼,오 검사)
		if ((child < h->heap_size) && (h->heap[child] > h->heap[child + 1])) {
			child++;
		}
		if (temp <= h->heap[child]) { // 말단 노드가 child 보다 더 밑으로 내려갈 수 없음
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // 루트값 반환
}
void heap_max_sort(int a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0; i < n; i++) {
		insert_min_heap(h, a[i]);
	}
	for (i = 0;  i < 100; i++) {
		a[i] = delete_min_heap(h);
	}
	free(h);
}

void heap_min_sort(int a[], int n) {
	int i;
	HeapType* h;

	h = create();
	init(h);

	for (i = 0; i < n; i++) {
		insert_max_heap(h, a[i]);
	}
	for (i = 0; i < 100; i++) {
		a[i] = delete_max_heap(h);
	}
	free(h);
}

void main() {
	int cnt = 0;

	int* random = (int*)malloc(sizeof(int)*100);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 100; i++) {
		random[i] = rand() % 100;
		for (int j = 0; j < i; j++) {
			if (random[i] == random[j]) {
				i--;
				break;
			}
		}
	}
	printf("\t<정렬할 데이터 초기화>\t\n");
	for (int i = 0; i < 100; i++) {
		printf("%2d  ", random[i]);
		cnt++;
		if (cnt % 10 == 0)
			printf("\n");
	}
	printf("\t오름차순 정렬 후\t\n");
	heap_max_sort(random, 100);
	cnt = 0;
	for (int i = 0; i < 100; i++) {
		printf("%2d  ", random[i]);
		cnt++;
		if (cnt % 10 == 0)
			printf("\n");
	}

	printf("\t내림차순 정렬 후\t\n");
	heap_min_sort(random, 100);
	cnt = 0;
	for (int i = 0; i < 100; i++) {
		printf("%2d  ", random[i]);
		cnt++;
		if (cnt % 10 == 0)
			printf("\n");
	}
	free(random);
}