#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
#define INDEX_SIZE 4 // 테이블의 크기가 너무 크면 보간 탐색 실패함 즉, 적당한 크기 설정 필요
#define SWAP(x,y,t) ( (t)=(x) , (x) = (y) , (y) =(t) )
/*색인 순차 탐색을 위한 구조체 선언*/
typedef struct itable {
	int key, index; // key 필드 : 인덱스가 가리키는 곳, index 필드 : 인덱스 값
}itable;
itable index_list[INDEX_SIZE];
// 이진 탐색 순환호출
int search_binary(int key,int low,int high,int list[]) {
	int middle;

	if (low <= high) { // 탐색 가능한 경우
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key < list[middle])
			return search_binary(key, low, middle - 1, list); // 왼쪽 부분 리스트 검색
		else
			return search_binary(key, middle + 1, high, list); // 오른쪽 부분 리스트 검색
	}

	return -1; // 탐색 실패
}

// 이진 탐색 반복이용
int search_binary2(int key, int low, int high, int list[]) {
	int middle;

	while (low <= high) { // 탐색 가능한 경우
		middle = (low + high) / 2;
		if (key == list[middle])
			return middle;
		else if (key > list[middle])
			low = middle + 1;
		else
			high = middle - 1;
	}

	return -1; // 탐색 실패
}
// 보간 탐색 순환호출
int recusive_interpolation_search(int ar[], int first, int last, int target) {
	int mid;

	//탈출 조건
	if (ar[first] > target || ar[last] < target) {
		return -1;
	}

	//보간 탐색 관계식
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
// 순차 탐색
int seq_search(int key, int low, int high, int list[]) {
	int i;

	for (i = low;i <= high;i++) {
		if (list[i] == key)
			return i;
	}
	return -1;
}
// 개선된 순차탐색
int seq_search2(int key, int low, int high, int list[]) {
	int i;
	list[high + 1] = key;

	for (i = low;list[i] != key;i++);// 키 값을 찾으면 종료

	if (i == (high + 1))
		return -1; // 탐색 실패
	else
		return i; // 탐색 성공
}
// 색인 순차 탐색을 위한 인덱스 테이블 생성 함수
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

// 색인 순차 탐색
int search_index(int key, int n, int list[]) {
	int i, low, high;

	// 키 값이 리스트 범위 내의 값이 아니면 탐색 종료
	if (key < list[0] || key > list[n - 1])
		return -1;

	// 인덱스 테이블을 조사하여 해당키의 구간 결정
	for (i = 0; i < INDEX_SIZE; i++) {
		if (index_list[i].key <= key && index_list[i + 1].key > key)
			break;
	}

	if (i == INDEX_SIZE) { // 인덱스 테이블의 끝이면
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
	printf("몇 개의 데이터를 삽입하시겠습니까 ? ");
	int n, search;
	scanf("%d", &n);

	int *list = (int *)malloc(sizeof(int)*n);

	for (int i = 0; i < n; i++) {
		list[i] = rand() % n;
		printf("%d ", list[i]);
	}

	quick_sort(list, 0, n - 1); // 정렬

	printf("\n탐색 하시려는 값을 입력하세요 : ");
	scanf("%d", &search);

	// 이진 탐색 순환 호출
	int flag1 = search_binary(search, 0, n - 1, list);
	if (flag1 != -1)
		printf("탐색성공\n");
	else
		printf("탐색실패\n");

	// 이진 탐색 반복
	int flag2 = search_binary2(search, 0, n - 1, list);
	if (flag2 != -1)
		printf("탐색성공\n");
	else
		printf("탐색실패\n");

	// 보간 탐색 순환 호출
	int flag3 = recusive_interpolation_search(list,0,n-1,search);
	if (flag3 != -1)
		printf("탐색성공\n");
	else
		printf("탐색실패\n");

	int flag4 = interpolation_search(search, n, list);
	if (flag4 != -1)
		printf("탐색성공\n");
	else
		printf("탐색실패\n");

	makeIndexTable(list, n);

	int flag5 = search_index(search, n, list);
	if (flag5 != -1)
		printf("탐색성공\n");
	else
		printf("탐색실패\n");

}

