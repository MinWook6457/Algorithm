#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

#define KEY_SIZE 10 // Ž��Ű �ִ����
#define TABLE_SIZE 13 // �ؽ� ���̺� ũ�� = �Ҽ�

#define empty(item) (strlen(item.key)==0) // ���� ��Ŷ�� ����ִ°�?
#define equal(item1,item2) (!strcmp(item1.key,item2.key)) // �� �׸��� �����Ѱ�?

typedef struct {
	char key[KEY_SIZE];
}element;

element hash_table[TABLE_SIZE]; // �ؽ� ���̺� ����

// �ؽ� ���̺��� �� ��� �ʱ�ȭ
void init_table(element *ht) {
	for (int i = 0; i < TABLE_SIZE; i++) {
		ht[i].key[0] = NULL; // ù ��° ���ڰ� NULL ���̸� ��Ŷ�� ��������� ����.
	}
}

// Ű -> ���� �ؽ� �Լ�
// ���ڿ� -> ���� -> ���� �Լ�
int transform(char *key) {
	int number = 0;
	while (*key) {
		number = number + *key++; // ���� �Լ� : ȣ���� ���
	}
	return number;
}

// ���� �Լ� ����� �ؽ� �Լ�
int hash_function(char *key) {
	return transform(key) % TABLE_SIZE; // Ű�� �ڿ����� ��ȯ�� ���� ���̺��� ũ��� ������ �������� ��ȯ
}

// �ؽ� ���̺� ���� �Լ�
// ���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ� , ���̺��� ���� �� ��� ����
void hash_lp_add(element item, element *ht) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "Ž��Ű�� �ߺ��Ǿ����ϴ�\n");
			exit(1);
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_table) {
			fprintf(stderr, "���̺��� ����á���ϴ�\n");
			exit(1);
		}
	}

	ht[i] = item;
}

// ����� �׸� Ž�� �Լ�
// Ž���� ���������� ���� Ű�� �ؽ� �Լ��� ���� ��Ű�� �׸��� ã�� ���ϸ� 
// �ش� �׸��� ã�� �� ���� ���ӵ� ��Ŷ�� Ž����

void hash_lp_search(element item, element *ht) {
	int i, hash_value;
	hash_value = i = hash_function(item.key);

	while (!empty(ht[i])) {
		if (equal(item, ht[i])) {
			fprintf(stderr, "Ž�� : %s ��ġ = %d\n", item.key, i); // Ž�� ����
			return;
		}

		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value) {
			fprintf(stderr, "ã�� ���� ���̺� ����\n");
			exit(1);
		}
	}
	fprintf(stderr, "ã�� ���� ���̺� ����\n");
}

// �ؽ� ���̺� ���� ���
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
	char *temp[100]; // ���ڿ��� ������ �迭 ������
	char *ch; // �����Ҵ��� ���� ������
	char buffer[100];
	int *index;
	if (fp == NULL) {
		fprintf(stderr, "File open error\n");
		exit(1);
	}
	int nCount = 0; // ���ڿ��� ����
	while (!feof(fp)) {
		fgets(temp, stdin, fp);
		nCount++;
	}
	rewind(fp); // ���������� ����ġ
	index = (int *)malloc(sizeof(int)*nCount); //������ ������ŭ �ε��� �����Ҵ�
	for (int i = 0; i < nCount; i++) {
		fgets(buffer, stdin, fp);
		index[i] = (int)strlen(buffer); // 0������ nCount������ �ε����� ���ڿ� ���� ����
	}
	rewind(fp); // ���������� ����ġ
	for (int i = 0; i < nCount; i++) {
		ch = (char *)malloc(sizeof(char)*index[i]); // ���ڿ� ���̸�ŭ �����Ҵ�
		fscanf(fp, "%s", ch);
		temp[i] = ch; // �迭 �����Ϳ� �޾ƿ� ���ڿ� ����
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
