#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int list[MAX_SIZE];

void inc_insertion_sort(int list[], int first, int last, int gap) {
	int i, j, key;

	for (i = first + gap; i <= last; i += gap) {
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j -= gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shell_sort(int list[], int n) {
	int i, gap;
	for (gap = n / 2; gap > 0;gap /= 2) {
		if (gap % 2 == 0)
			gap++;
		for (i = 0; i < gap;i++) {
			inc_insertion_sort(list, i, n - 1, gap);
		}
	}
}

void main() {
	int n = MAX_SIZE;
	printf("정렬전\n");
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
		printf("%d ", list[i]);
	}
	printf("\n정렬후\n");
	shell_sort(list, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
}