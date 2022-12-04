#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define KEY_SIZE 10 // 탐색키 최대길이
#define TABLE_SIZE 13 // 해싱 테이블 크기 = 소수

#define empty(item) (strlen(item.key)==0) // 현재 버킷이 비어있는가?
#define equal(item1,item2) (!strcmp(item1.key,item2.key)) // 두 항목이 동일한가?

typedef struct {
	char key[KEY_SIZE];
}element;

element hash_table[TABLE_SIZE]; // 해싱 테이블 선언

// 해시 테이블의 각 요소 초기화
void init_table(element *ht) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL; // 첫 번째 문자가 NULL 값이면 버킷이 비어있음을 뜻함.
	}
}

// 키 -> 정수 해시 함수
// 문자열 -> 정수 -> 제산 함수
int transform(char *key) {
	int number = 0;
	while (*key) {
		number = number + *key++; // 제산 함수 : 호너의 방법
	}
	return number;
}

// 제산 함수 사용한 해싱 함수
int hash_function(char *key) {
	return transform(key) % TABLE_SIZE; // 키를 자연수로 변환한 다음 테이블의 크기로 나누어 나머지를 반환
}

// 해시 테이블 삽입 함수
// 선형 조사법을 이용하여 테이블에 키를 삽입하고 , 테이블이 가득 찬 경우 종료
void hash_lp_add(element item, element *ht) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색키가 중복되었습니다\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_table) {
			fprintf(stderr, "테이블이 가득찼습니다\n");
			exit(1);
		}
	}

	ht[i] = item;
}

// 저장된 항목 탐색 함수
// 탐색도 마찬가지로 먼저 키에 해시 함수를 적용 시키고 항목을 찾지 못하면 
// 해당 항목을 찾을 때 까지 연속된 버킷을 탐색함

void hash_lp_search(element item, element *ht) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "탐색 : %s 위치 = %d\n", item.key, i); // 탐색 성공
			return;
		}

		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			fprintf(stderr, "찾는 값이 테이블에 없음\n");
			exit(1);
		}
	}
	fprintf(stderr, "찾는 값이 테이블에 없음\n");
}

// 해싱 테이블 내용 출력
void hash_lp_print(element *ht) {
	printf("=========================\n");
	for (int i = 0; i < TABLE_SIZE; i++) {
		printf("[%d] %s\n", i, ht[i].key);
	}
	printf("=========================\n");
}

void main() {
	FILE *fp;
	fp = fopen("hashing.txt", "r");
	char *temp[100]; // 문자열을 저장할 배열 포인터
	char *ch; // 동적할당을 위한 포인터
	char buffer[100];
	int *index;
	if (fp == NULL) {
		fprintf(stderr, "File open error\n");
		exit(1);
	}
	int nCount = 0; // 문자열의 개수
	while (!feof(fp)) {
		fgets(temp, stdin, fp);
		nCount++;
	}
	rewind(fp); // 파일포인터 원위치
	index = (int *)malloc(sizeof(int)*nCount); //파일의 개수만큼 인덱스 동적할당
	for (int i = 0; i < nCount; i++) {
		fgets(buffer, stdin, fp);
		index[i] = (int)strlen(buffer); // 0번부터 nCount번까지 인덱스에 문자열 길이 저장
	}
	rewind(fp); // 파일포인터 원위치
	for (int i = 0; i < nCount; i++) {
		ch = (char *)malloc(sizeof(char)*index[i]); // 문자열 길이만큼 동적할당
		fscanf(fp, "%s", ch);
		temp[i] = ch; // 배열 포인터에 받아온 문자열 저장
		printf("%s\n", temp[i]);
	}
	printf("\n");
	element e;
	
	for (int i = 0; i < nCount; i++) {
		strcpy(e.key, temp[i]);
		hash_lp_add(e, hash_table);
		
	}
	hash_lp_print(hash_table);

	for (int i = 0; i < nCount; i++) {
		strcpy(e.key, temp[i]);
		hash_lp_search(e, hash_table);
	}
	
}
