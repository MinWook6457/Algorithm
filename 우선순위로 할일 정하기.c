#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 200
#pragma warning(disable:4996)
typedef struct
{
	int rank;
	char* work;
} element;
typedef struct
{
	element heap[MAX_ELEMENT];
	char work;
	int heap_size;
} HeapType;
// 생성 함수
HeapType* create()
{
	return (HeapType*)malloc(sizeof(HeapType));
}
// 초기화 함수
void init(HeapType* h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_max_heap(HeapType* h, element item)
{
	int i;
	i = ++(h->heap_size);

	while ((i != 1) && (item.rank > h->heap[i / 2].rank)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}
// 삭제 함수
element delete_max_heap(HeapType* h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size)
	{
		if ((child < h->heap_size) && (h->heap[child].rank) < h->heap[child + 1].rank)
			child++;
		if (temp.rank >= h->heap[child].rank) 
			break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
void main()
{
	HeapType* heap;
	heap = create();
	init(heap);

	char select;
	char works[50];
	int rank;
	while (1)
	{
		printf("삽입(i), 삭제(d) : ");
		scanf("%c", &select); 
		getchar();
		if (select == 'd')
			break;
		else if (select == 'i')
		{
			printf("할일: ");
			fgets(works, 50, stdin);
			printf("우선순위: ");
			scanf("%d", &rank);
			getchar();
			element tmp;
			tmp.rank = rank;
			tmp.work = works;
			insert_max_heap(heap, tmp);
		}else{
			element result = delete_max_heap(heap);
			printf("제일 우선 순위가 높은 일은 %s", result.work);
			break;
		}
	}
	free(heap);
}
