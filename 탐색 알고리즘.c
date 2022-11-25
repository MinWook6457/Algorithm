#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define INDEX_SIZE 4 // ���̺��� ũ�Ⱑ �ʹ� ũ�� ���� Ž�� ������ ��, ������ ũ�� ���� �ʿ�
#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )
/*���� ���� Ž���� ���� ����ü ����*/
typedef struct itable {
	int key, index; // key �ʵ� : �ε����� ����Ű�� ��, index �ʵ� : �ε��� ��
}itable;
itable index_list[INDEX_SIZE];
// ���� Ž�� ��ȯȣ��
int search_binary(int key,int low,int high,int list[]) {
	int middle;

	if (low <= high) { // Ž�� ������ ���
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key < list[middle])
			return search_binary(key, low, middle - 1, list); // ���� �κ� ����Ʈ �˻�
		else
			return search_binary(key, middle + 1, high, list); // ������ �κ� ����Ʈ �˻�
	}

	return -1; // Ž�� ����
}

// ���� Ž�� �ݺ��̿�
int search_binary2(int key, int low, int high, int list[]) {
	int middle;

	while (low <= high) { // Ž�� ������ ���
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1; // Ž�� ����
}
// ���� Ž�� ��ȯȣ��
int recusive_interpolation_search(int ar[], int first, int last, int target) {
	int mid;

	//Ż�� ����
	if (ar[first] > target || ar[last] < target) {
		return -1;
	}

	//���� Ž�� �����
	mid = ((double)(target - ar[first]) / (ar[last] - ar[first]) * (last - first)) + first;

	if (target == ar[mid]) {
		return mid;
	}
	else if (target < ar[mid]) {
		return recusive_interpolation_search(ar, first, mid - 1, target);
	}
	else {
		return recusive_interpolation_search(ar, mid + 1, last, target);
	}
}

int interpolation_search(int key, int n, int list[]) {
	int low, high, j;

	low = 0;
	high = n - 1;
	while ((list[high]) >= key && (list[low]) < key) {
		j = ((float)(key - list[low]) / (list[high] - list[low])*(high - low)) + low;
		if (key < list[j])
			low = j + 1;
		else if (key > list[j])
			high = j - 1;
		else
			low = j;
	}

	if (list[low] == key)
		return low;
	else
		return -1;
}
// ���� Ž��
int seq_search(int key, int low, int high, int list[]) {
	int i;

	for (i = low;i <= high;i++) {
		if (list[i] == key)
			return i;
	}
	return -1;
}
// ������ ����Ž��
int seq_search2(int key, int low, int high, int list[]) {
	int i;
	list[high + 1] = key;

	for (i = low;list[i] != key;i++);// Ű ���� ã���� ����

	if (i == (high + 1))
		return -1; // Ž�� ����
	else
		return i; // Ž�� ����
}
// ���� ���� Ž���� ���� �ε��� ���̺� ���� �Լ�
void makeIndexTable(int list[], int size) {
	int i, n;
	n = size / INDEX_SIZE;
	if (size%INDEX_SIZE > 0)
		n = n + 1;

	for (i = 0; i < INDEX_SIZE; i++) {
		index_list[i].index = i * n;
		index_list[i].key = list[i*n];
	}
}

// ���� ���� Ž��
int search_index(int key, int n, int list[]) {
	int i, low, high;

	// Ű ���� ����Ʈ ���� ���� ���� �ƴϸ� Ž�� ����
	if (key < list[0] || key > list[n - 1])
		return -1;

	// �ε��� ���̺��� �����Ͽ� �ش�Ű�� ���� ����
	for (i = 0; i < INDEX_SIZE; i++) {
		if (index_list[i].key <= key && index_list[i + 1].key > key)
			break;
	}

	if (i == INDEX_SIZE) { // �ε��� ���̺��� ���̸�
		low = index_list[i - 1].index;
		high = n;
	}
	else {
		low = index_list[i].index;
		high = index_list[i + 1].index;
	}

	return seq_search(key, low, high, list);
}

int partition(int list[], int left, int right) {
	int pivot, temp, low, high;

	low = left;
	high = right + 1;
	pivot = list[left];

	do {
		do {
			low++;
		} while (list[low] < pivot);
		do {
			high--;
		} while (list[high] > pivot);
		if (low < high)
			SWAP(list[low], list[high], temp);
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
	printf("�� ���� �����͸� �����Ͻðڽ��ϱ� ? ");
	int n, search;
	scanf("%d", &n);

	int *list = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		list[i] = rand() % n;
		printf("%d ", list[i]);
	}

	quick_sort(list, 0, n - 1); // ����

	printf("\nŽ�� �Ͻ÷��� ���� �Է��ϼ��� : ");
	scanf("%d", &search);

	// ���� Ž�� ��ȯ ȣ��
	int flag1 = search_binary(search, 0, n - 1, list);
	if (flag1 != -1)
		printf("Ž������\n");
	else
		printf("Ž������\n");

	// ���� Ž�� �ݺ�
	int flag2 = search_binary2(search, 0, n - 1, list);
	if (flag2 != -1)
		printf("Ž������\n");
	else
		printf("Ž������\n");

	// ���� Ž�� ��ȯ ȣ��
	int flag3 = recusive_interpolation_search(list,0,n-1,search);
	if (flag3 != -1)
		printf("Ž������\n");
	else
		printf("Ž������\n");

	int flag4 = interpolation_search(search, n, list);
	if (flag4 != -1)
		printf("Ž������\n");
	else
		printf("Ž������\n");

	makeIndexTable(list, n);

	int flag5 = search_index(search, n, list);
	if (flag5 != -1)
		printf("Ž������\n");
	else
		printf("Ž������\n");

}

