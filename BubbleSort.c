////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� : 2022�� 09�� 06��
// ���α׷��� : ���������, ���Ḯ��Ʈ, �����Ҵ�, ������ �̿��� �л� ������ ����
// ���α׷����� : data.txt ���Ͽ� �й�, �̸�, ������ ����Ǿ��ִ�. 
//				  ������ ���� �Ҵ��� �̿��Ͽ� �ܼ� ���Ḯ��Ʈ�� �Է� �޾� �����ϰ�, 
//				  ���Ḯ��Ʈ���̿��Ͽ� �й�, �̸�, ���� ������ ����
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h> // strcmp �Լ� ���
#pragma warning(disable:4996)
typedef struct {
	int number;
	char name[20];
	double total;
}student;
typedef struct LinstNode {
	student data;
	struct ListNode *link;
} ListNode;
ListNode *insert_first(ListNode *head, student st) // ��� �� �տ� ����
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = st;
	p->link = head;
	head = p;
	return head;
}

ListNode *bubble(ListNode *head, int n) // ������ �ڵ�!
{
	for (int i = 0; i < n; i++) {
		ListNode* current = head; // �����尡 �������
		ListNode* next = current->link; // �������� ��ũ�� ����Ű�� ���� ��带 ����Ŵ
		ListNode* previous = NULL; // ��������� �ʱⰪ ���� = NULL

		while (next != NULL) {
			if (current->data.total < next->data.total) { // ��������
				if (current == head) { // �����尡 head�� ����Ű�� next�� �������� ��ũ�� ����ų �� next����� ���� ū ���
					head = next; // ��� ������ ����
				}
				else { // ���� ����� ��ũ�� ���� ��带 ����Ŵ
					previous->link = next;
				}
				current->link = next->link;
				next->link = current;

				previous = next;
				next = current->link;
			}
			else {
				previous = current;
				current = current->link;
				next = current->link;
			}
		}
	}
	return head;
}
/*
void bubble_sort_name(ListNode *head) { // �̸��� ���� ���� strcmp �Լ� ���
	ListNode *p, *q;
	student tmp;

	for (p = head;p != NULL;p = p->link) { // ��� p�� �Ӹ���� ���� �˻�
		for (q = p;q != NULL;q = q->link) { // q�� p��带 ����
			if (strcmp(p->data.name, q->data.name) > 0) { // q����� �й��� p����� �й����� ������� swap
				tmp = p->data;
				p->data = q->data;
				q->data = tmp;
			}
		}
	}
}
*/
void display(ListNode *head)
{
	ListNode* p = head; // ���Ḯ��Ʈ ����
	printf("�� ��    ���� �� �� ��  ���� �� \n");
	printf("������������������������������������������������������\n");
	while (p != NULL)
	{
		printf("�� %d  %s    %.1lf ��\n", p->data.number, p->data.name, p->data.total);
		p = p->link;
	}
	printf("������������������������������������������������������\n\n");
	printf("\n");
}
void main()
{
	FILE *fp = NULL;
	ListNode *list = NULL;
	student stu;
	int count = 0;
	fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("������ ���µ� �����߽��ϴ�.");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &stu.number, stu.name, &stu.total);
		count++;
		list = insert_first(list, stu);
	}
	printf("======������ �����Ͱ�======\n");
	display(list);
	printf("======�������� ������======\n");
	list = bubble(list, count);
	display(list);
	//free(list1);
	fclose(fp);
}