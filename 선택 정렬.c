#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )

int list[MAX_SIZE];

void selection_sort(int list[], int n) {
	int i, j, least, temp;

	for (int i = 0; i < n - 1; i++) {
		least = i;
		for (int j = i + 1; j < n; j++) {
			if (list[j] < list[least])
				least = j;
		}
		SWAP(list[i], list[least], temp);
	}
}

void main() {
	int n = MAX_SIZE;

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}

	selection_sort(list, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
}