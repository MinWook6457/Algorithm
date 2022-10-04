#include <stdio.h>
#include <stdlib.h>
// ������ Ư��
// ��������Ʈ��
// �ߺ������� ���
// �ִ� Ȥ�� �ּ� ���� ����
// uphead , downheap
#pragma warning(disable:4996)

typedef struct {
	int key;
	// char animal[100];
}element;
// ���� ��� = �θ��ε��� * 2
// ������ ��� = �θ��ε��� * 2 + 1
// �θ��� = �ڽ��ε��� / 2
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

	//i�� ��Ʈ�� �ƴϰ� i��° ��尡 �θ� ��庸�� ũ��
	while ((i != 1) && data.key > h->heap[i / 2].key) {
		// �ڸ��ٲ�
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = data;
}
element max_heap_delete(HeapType *h) {
	int parent, child;
	element temp, item;

	item = h->heap[1]; // ��Ʈ�� ��ȯ�� ���� ����
	temp = h->heap[(h->heap_size)--]; // ���� ��� ����
	parent = 1; // �θ��� �ε��� �ʱⰪ ����
	child = 2; // �ڽĳ�� �ε��� �ʱⰪ ����

	while (child <= h->heap_size) {
		// ���� ����� �ڽ� ��� �߿��� �� ū �ڽĳ�带 ã�´�. (�θ� ���� ��,�� �˻�)
		if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
			child++;
		}
		if (temp.key >= h->heap[child].key) { // ������ ���� ���� ū ���̰ų� ���� �������� ���� Ʈ���� ������ ��� while�� ����
			break;
		}
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;

	}
	h->heap[parent] = temp;
	return item; // ��Ʈ�� ��ȯ
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
		fprintf(stderr, "���� ���� ����\n");
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