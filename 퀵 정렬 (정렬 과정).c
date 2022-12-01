#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)
#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )

int partition(int list[], int left, int right) {
	int pivot, temp, low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	printf("\n-Pivot - : %d -\n", pivot);

	printf("\n");

	do {
		do {
			low++;
		} while (low <= right && list[low] < pivot);
		do {
			high--;
		} while (high >= left && list[high] > pivot);
		printf("Low : %d High : %d\n", list[low], list[high]);
		for (int i = 0; i < right + 1; i++)
			printf("%d > ", list[i]);
		if (low < high) {
			printf("\n%d와 %d 스왑\n", list[low], list[high]);
			SWAP(list[low], list[high], temp);
			for (int i = 0; i < right + 1; i++)
				printf("%d > ", list[i]);
			printf("\n");
		}
	} while (low < high);
	SWAP(list[left], list[high], temp);

	return high;
}

void quick_sort(int list[], int left, int right) {
	if (left < right) {
		int p = partition(list, left, right);
		quick_sort(list, left, p - 1);
		quick_sort(list, p + 1, right);
	}
}

void main() {
	FILE* fp;

	fp = fopen("quick.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int count = 0;
	int tmp;
	while (!feof(fp)) {
		fscanf(fp, "%d", &tmp);
		count++;
	}
	int* list = (int*)malloc(sizeof(int) * count);

	rewind(fp);

	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d", &list[i]);
	}
	printf("정렬 전 리스트 : ");
	for (int i = 0; i < count; i++)
		printf("%d > ", list[i]);


	quick_sort(list, 0, count - 1);

	printf("\n정렬 후 리스트 : ");
	for (int i = 0; i < count; i++)
		printf("%d > ", list[i]);

}
