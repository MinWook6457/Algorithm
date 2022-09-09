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
ListNode *inser_first(ListNode *head, student st) // ��� �� �տ� ����
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = st;
	p->link = head;
	head = p;
	return head;

}
ListNode *bubble_sort_grade(ListNode *head) { // ������ ���� ����
	ListNode *p, *q, *r; 

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (q->data.total > p->data.total) { // q�� ������ p�� �������� ū ��� swap
				r = p->data; // p����� �����͸� ���ۿ� ����
				p->data = q->data; // q�����͸� p�����Ϳ� ����
				q->data = r; // ���ۿ� �ִ� p����� �����͸� q��忡 ����
			}
		}
	}
	return r;
}
/*
void bubble_sort_grade(ListNode *head) { // ������ ���� ����
	ListNode *p, *q;
	student tmp; // ����� �����͸� �ٲٱ� ���� ����

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (q->data.total > p->data.total) { // q�� ������ p�� �������� ū ��� swap
				tmp = p->data; // p����� �����͸� ���ۿ� ����
				p->data = q->data; // q�����͸� p�����Ϳ� ����
				q->data = tmp; // ���ۿ� �ִ� p����� �����͸� q��忡 ����
			}
		}
	}
}
*/
ListNode  *bubble_sort_number(ListNode *head) { // �й��� ���� ����
	ListNode *p, *q, *r;

	for (p = head;p != NULL;p = p->link) { // ��� p�� �Ӹ���� ���� �˻�
		for (q = p;q != NULL;q = q->link) { // q�� p��带 ����
			if (q->data.number < p->data.number) { // q����� �й��� p����� �й����� ������� swap
				r = p->data;
				p->data = q->data;
				q->data = r;
			}
		}
	}
	return r;
}

ListNode *bubble_sort_name(ListNode *head) { // �̸��� ���� ���� strcmp �Լ� ���
	ListNode *p, *q, *r;

	for (p = head;p != NULL;p = p->link) { // ��� p�� �Ӹ���� ���� �˻�
		for (q = p;q != NULL;q = q->link) { // q�� p��带 ����
			if (strcmp(p->data.name,q->data.name)>	0) { // q����� �й��� p����� �й����� ������� swap
				r = p->data;
				p->data = q->data;
				q->data = r;
			}
		}
	}
	return r;
}
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
void main()
{
	FILE *fp = NULL;
	ListNode *list = NULL;
	student stu;

	fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("������ ���µ� �����߽��ϴ�.");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &stu.number, stu.name, &stu.total);
		printf("%d %s %.1lf\n", stu.number, stu.name, stu.total);
		list = inser_first(list, stu);
		// insert_node(&list, NULL, create_node(stu, NULL)); // ���԰� ���ÿ� ���ο� ��� ����
	}
	printf("======�������� ������======\n");
	bubble_sort_grade(list);
	display(list);
	printf("======�������� �й���======\n");
	bubble_sort_number(list);
	display(list);
	printf("======�������� �̸���======\n");
	bubble_sort_name(list);
	display(list);
	//free(list1);
	fclose(fp);
}