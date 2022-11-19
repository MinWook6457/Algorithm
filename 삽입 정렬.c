#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

int list[MAX_SIZE];

void insertion_sort(int list[], int n) {
	int key;
	int j;
	for (int i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j] >= key; j--) {
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}

void main() {
	int n = MAX_SIZE;

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}

	insertion_sort(list, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
}