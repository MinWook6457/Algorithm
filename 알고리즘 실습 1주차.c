#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct {
	int hak;
	char name[20];
	int mat, eng, kor, tot;
	double avg;
}student;

typedef struct LinstNode {
	student data;
	struct ListNode *link;
} ListNode;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void insert_node(ListNode **phead, ListNode *p, ListNode *new_node)
{
	if (*phead == NULL) { // ���� ���Ḯ��Ʈ �ΰ��
		new_node->link = NULL; // ���� ����Ʈ ù ����� ��ũ�� �ʱ�ȭ
		*phead = new_node; // ����Ʈ ��忡 ����
	}
	else if (p == NULL) { 
		new_node->link = *phead;
		*phead = new_node;
	}
	else {
		new_node->link = p->link;
		p->link = new_node;
	}
}
void free(ListNode *head) {
	ListNode *p = head;
	ListNode *next;
	while (p != NULL) {
		next = p->link;
		free(p);
		p = next;
	}
}

void display(ListNode *head)
{
	ListNode* p = head;
	printf("����������������������������������������������������������������������������������������������������������������\n");
	printf("�� ��    ���� �� �� �� ���� �� ���� �� ���� �� ���� �� ��  �� ��\n");
	printf("����������������������������������������������������������������������������������������������������������������\n");
	while (p != NULL)
	{ 
		printf("  %d  %s  %d     %d     %d    %d    %lf\n", p->data.hak, p->data.name, p->data.mat, p->data.eng, p->data.kor, p->data.tot, p->data.avg);
		p = p->link;
	}
	printf("����������������������������������������������������������������������������������������������������������������\n\n");
	printf("\n");

}
ListNode *create_node(student data, ListNode *link)
{
	ListNode* new_node = (ListNode *)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	new_node->data = data;
	new_node->link = link;
	return new_node;

}
void bubble_sort(ListNode *head) {
	ListNode *p, *q;
	student tmp;

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (q->data.tot > p->data.tot) { // q�� ������ p�� �������� ū ��� swap
				tmp = p->data;
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
}
void main()
{
	FILE *fp = NULL;
	ListNode *list1 = NULL;
	student tmp;

	fp = fopen("data2.txt", "r");

	if (fp == NULL)
	{
		printf("������ ���µ� �����߽��ϴ�.");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %d %d %d", &tmp.hak, tmp.name, &tmp.mat, &tmp.eng, &tmp.kor);
		tmp.tot = tmp.mat + tmp.eng + tmp.kor;
		tmp.avg = tmp.tot / 3.0;
		printf("%d\t%s\t%d\t%d\t%d\t%d\t%lf\n", tmp.hak, tmp.name, tmp.mat, tmp.eng, tmp.kor,tmp.tot , tmp.avg);
		insert_node(&list1, NULL, create_node(tmp, NULL));
		bubble_sort(list1);
	}

	display(list1);
	free(list1);
	fclose(fp);
}