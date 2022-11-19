#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )
int list[MAX_SIZE];

void BubbleSort(int list[], int n) {
	int i, j, temp;

	for (i = n - 1;i > 0;i--) {
		for (j = 0;j < i;j++) {
			if (list[j] > list[j + 1])
				SWAP(list[j], list[j + 1], temp);
		}
	}
}

void main() {
	int n = MAX_SIZE;

	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		list[i] = rand() % 100;
	}

	BubbleSort(list, n);

	for (int i = 0; i < n; i++) {
		printf("%d ", list[i]);
	}
}