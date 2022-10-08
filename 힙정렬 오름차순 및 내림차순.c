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

	item = h->heap[1]; // ��Ʈ�� ��ȯ�� ���� ����
	temp = h->heap[(h->heap_size)--]; // ���� ��� ����
	parent = 1; // �θ��� �ε��� �ʱⰪ ����
	child = 2; // �ڽĳ�� �ε��� �ʱⰪ ����

	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �߿��� �� ū �ڽĳ�带 ã�´�. (�θ� ���� ��,�� �˻�)
		if ((child < h->heap_size) && (h->heap[child] < h->heap[child + 1])) {
			child++;
		}
		if (temp >= h->heap[child]) { // ������ ���� ���� ū ���̰ų� ���� �������� ���� Ʈ���� ������ ��� while�� ����
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // ��Ʈ�� ��ȯ
}

int delete_min_heap(HeapType* h) {
	int parent, child;
	int temp, item;

	item = h->heap[1]; // ��Ʈ�� ��ȯ�� ���� ����
	temp = h->heap[(h->heap_size)--]; // ���� ��� ����
	parent = 1; // �θ��� �ε��� �ʱⰪ ����
	child = 2; // �ڽĳ�� �ε��� �ʱⰪ ����

	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �߿��� �� ū �ڽĳ�带 ã�´�. (�θ� ���� ��,�� �˻�)
		if ((child < h->heap_size) && (h->heap[child] > h->heap[child + 1])) {
			child++;
		}
		if (temp <= h->heap[child]) { // ���� ��尡 child ���� �� ������ ������ �� ����
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // ��Ʈ�� ��ȯ
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
	printf("\t<������ ������ �ʱ�ȭ>\t\n");
	for (int i = 0; i < 100; i++) {
		printf("%2d  ", random[i]);
		cnt++;
		if (cnt % 10 == 0)
			printf("\n");
	}
	printf("\t�������� ���� ��\t\n");
	heap_max_sort(random, 100);
	cnt = 0;
	for (int i = 0; i < 100; i++) {
		printf("%2d  ", random[i]);
		cnt++;
		if (cnt % 10 == 0)
			printf("\n");
	}

	printf("\t�������� ���� ��\t\n");
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