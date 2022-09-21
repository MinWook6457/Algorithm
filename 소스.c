
#include <stdio.h>
#pragma warning(disable:4996)
int zero = 0;
int one = 0;
int fibonach(int n) {
	if (n == 0) {
		++zero;
		return 0;
	}
	else if (n == 1) {
		++one;
		return 1;
	}
	else
	{
		return fibonach(n - 1) + fibonach(n - 2);
	}
}
int main() {
	int count;
	scanf("%d", &count);
	int *arr;
	arr = (int *)malloc(sizeof(int)*count);
	int n;
	for (int i = 0; i < count; i++) {
		scanf("%d", &n);
		arr[i] = fibonach(n);
	}
	for (int i = 0; i < count; i++) {
		printf("%d %d\n", zero, one);
	}

	return 0;
}