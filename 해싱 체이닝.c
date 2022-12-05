#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define TABLE_SIZE 10
typedef struct {
	int key;
}element;

typedef struct list {
	element item;
	struct list *link;
}list;

list *hash_table[TABLE_SIZE];

int hash_function(int key) {
	return key % TABLE_SIZE;
}

void hash_chain_add(element item, list *ht[]) {
	int hash_value = hash_function(item.key);

	list *ptr;
	list *node_before = NULL, *node = ht[hash_value];

	for (;node;node_before = node, node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "이미 탐색키가 저장되어 있음\n");
			return;
		}
	}
	
	ptr = (list *)malloc(sizeof(list));
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)
		node_before->link = ptr;
	else
		ht[hash_value] = ptr;
}

void hash_chain_search(element item, list *ht[]) {
	list *node;

	int hash_value = hash_function(item.key);

	for (node = ht[hash_value];node;node = node->link) {
		if (node->item.key == item.key) {
			fprintf(stderr, "탐색 %d 성공\n",item.key);
			return;
		}
	}
	printf("키를 찾지 못했음\n");
}

void hash_chain_print(list *ht[]) {
	list *node;

	printf("================================\n");
	for (int i = 0; i < TABLE_SIZE;i++) {
		printf("[%d]->", i);
		for (node = ht[i];node;node = node->link) {
			printf("%d -> ", node->item.key);
		}
		printf("\n");
	}
	printf("================================\n");
}

void main() {
	FILE *fp = fopen("chaining.txt", "r");

	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	int x;
	int count = 0;
	while (!feof(fp)) {
		fscanf(fp, "%d", &x);
		count++;
	}
	rewind(fp);
	int *data = (int *)malloc(sizeof(int)*count);
	for (int i = 0; i < count; i++) {
		fscanf(fp, "%d ", &data[i]);
	}

	element e;

	for (int i = 0; i < count; i++) {
		e.key = data[i];
		hash_chain_add(e, hash_table);
	}
	hash_chain_print(hash_table);

	for (int i = 0; i < count; i++) {
		e.key = data[i];
		hash_chain_search(e, hash_table);
	}
}

