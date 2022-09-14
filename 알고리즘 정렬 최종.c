////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� : 2022�� 09�� 11��
// ���α׷��� : ���������, ���Ḯ��Ʈ, �����Ҵ�, ������ �̿��� �л� ������ ����
// ���α׷����� : data.txt ���Ͽ� �й�, �̸�, ������ ����Ǿ��ִ�. 
//				  ������ ���� �Ҵ��� �̿��Ͽ� �ܼ� ���Ḯ��Ʈ�� �Է� �޾� �����ϰ�, 
//				  ���Ḯ��Ʈ���̿��Ͽ� �й�, �̸�, ���� ������ ����
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <malloc.h>
#include <time.h> // �ð� ���� �Լ�
#include <string.h> // strcmp �Լ� ���
#pragma warning(disable:4996)
typedef struct { // ����ü ����
	int number; // �й�
	char *name; // �̸�
	double total; // ����
}student;

typedef struct ListNode { // ���Ḯ��Ʈ ����ü ����
	student data; // ����� �����Ͱ�
	struct ListNode *link; // ���Ḯ��Ʈ ��ũ
} ListNode;
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 09�� 11��
// �Լ��� : insert_first()
// �Լ����� : ����Ʈ�� ���� �κп� �׸��� �����ϴ� �Լ�
// �Լ��Է�: ��� �����Ϳ� ���Ӱ� �߰��Ǵ� ������
// �Լ����: ����� ��� ������
//			
////////////////////////////////////////////////////////////////
ListNode *insert_first(ListNode *head, student st) // ��� �� �տ� ����
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // ���� �޸� �Ҵ��� ���Ͽ� ���ο� ��� p ����
	if (p == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	p->data = st; // p->data�� st ����
	p->link = head; // ��� �������� ���� ����
	head = p; // ��� ������ ����
	return head; // ����� ��� ������ ��ȯ
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 09�� 11��
// �Լ��� : bubble()
// �Լ����� : ���� ���� �˰����� �̿��Ͽ� ���Ḯ��Ʈ�� ��ũ���� �����Ͽ� �����ϴ� �Լ�
// �Լ��Է� : ��� �����Ϳ� ���Ḯ��Ʈ ����� ����
// �Լ���� : ���Ḯ��Ʈ�� ������ ���� ���� �������� �����Ͽ� ��������� ����
//			
////////////////////////////////////////////////////////////////
ListNode *bubble(ListNode *head, int n) // ������ �ڵ�!
{
	for (int i = 0; i < n; i++) {
		ListNode* current = head; // �����尡 �������
		ListNode* next = current->link; // �������� ��ũ�� ����Ű�� ���� ��带 ����Ŵ
		ListNode* previous = NULL; // ��������� �ʱⰪ ���� = NULL

		while (next != NULL) {
			if (current->data.number > next->data.number) { // ��������
				if (current == head) { // �����尡 head�� ����Ű�� next�� �������� ��ũ�� ����ų �� next����� ���� ū ���
					head = next; // ��� ������ ����
				}
				else { // ���� ����� ��ũ�� ���� ��带 ����Ŵ
					previous->link = next;
				}
				current->link = next->link; // current->link ���� next->link�� ����Ű�� ������ ����
				next->link = current; // next->link�� current�� ����Ŵ

				previous = next; // ���� ��带 �� ��尡 ����Ű�� ������ ����
				next = current->link; // current->link�� ����ũ�� ���� next�� ����Ű���� ����
			}
			else {
				previous = current; // ���� ��� ���� ���� ��尡 ����Ű���� ����
				current = current->link; // ���� ��尪 �̵�
				next = current->link; // ���� ��尪 �̵�
			}
		}
	}
	return head;
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 09�� 11��
// �Լ��� : SelectSort()
// �Լ����� : ���� ���� �˰����� �̿��Ͽ� ���Ḯ��Ʈ�� ��ũ���� �����Ͽ� �����ϴ� ��� �Լ�
// �Լ��Է� : ��� ������
// �Լ���� : ��� ȣ���� ���Ͽ� ��� �������� ��ũ ���� ��ȯ�ϰ� 
//			  ȣ���� ������ ����� ��� ������ ��ȯ		
////////////////////////////////////////////////////////////////
ListNode* SelectSort(ListNode* head) {
	ListNode* p, *q, *r; // head : ���� , p : Ž�������� , q : �ּҰ� , r : q�� �ճ��
	if (head->link == NULL) // ����Լ� ���� ���� , ���Ḯ��Ʈ�� head->link ���� NULL�� ��� ����Ʈ ����
		return;
	p = q = r = head; // p,q,r �ʱ�ȭ
	while (p != NULL) { // ���Ḯ��Ʈ�� �� ���� �˻�, �� �̻� q�� ��尡 p�� ��庸�� ũ�� ������� �ݺ� ����
		if (p->data.total > q->data.total) { // �� ����� ���� �� ū ��� ��� �̵�
			q = p; // q��尡 p��带 ����Ŵ
		}
		p = p->link; // p�̵� 
	}

	p = head; // ������ p �ʱ�ȭ
	while (p->link != NULL) {
		if (p->link == q) { // q�� ���� ����� ��� ��, p�� ������ ���� q�� ������ ������ �������
			r = p; // p�� ���� r�� ����
		}
		p = p->link; // p �̵�
	}
	if (head != q) // head�� q�� ���� ���ٴ� ���� ����Ʈ�� ���� �ǹ���
	{
		p->link = head; // p�� ��ũ�� ��尡 ����Ű�� ���� ����
		head = q; // ��尪 ����
		r->link = NULL; // r�� ������ ����̹Ƿ� NULL�� �ʱ�ȭ
	}
	head->link = (SelectSort(head->link)); // ����Լ� ȣ���� ���� head ������ ����
	return head;
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 09�� 14��
// �Լ��� : insertionSortList()
// �Լ����� : �������� �˰����� ����Ͽ� ���Ḯ��Ʈ�� ��ũ ���� �ٲپ� �����Ѵ�.
// �Լ��Է� : ��� ������, ����� ����
// �Լ���� : ���Ḯ��Ʈ�� �̸� ������ ���� ��,��,�� ������ �����Ѵ�.
//			  		
////////////////////////////////////////////////////////////////
ListNode* InsertionSort(ListNode* head, int count) { // p : key���� ���� ��� || q : p�� ������� || key : ���� ������ �Ǵ� ��
	for (int i = 0 ; i < count ; i++) { // ����� ���� ��ŭ �ݺ�
		ListNode *key = head; // head�� ����
		for (int k = 0; k < i; k++){
			key = key->link; // Ű ��� �̵�
		}
		for (int j = i ; j > 0; j--) { 
			ListNode *p = head;	// p�� ����Ű�� ��带 head�� ����
			ListNode *q = head; // q�� ����Ű�� ��带 head�� ����
			while (p) // p�� key�� ���󰡴� ���
			{	
				if (p == key) break;// p�� key�� ����Ű�� ��� �ݺ� ����
				if (p->link == key) break;// p�� key�� ���� ����� ��� �ݺ� ����
				p = p->link; // p ��� �̵�
			}
			while (q) // q�� p�� ���󰡴� ���
			{
				if (q == p)break; // p�� q�� ����Ű�� ��� �ݺ� ����
				if (q->link == p) break; // q�� p�� ���� ����� ��� �ݺ� ����
				q = q->link;
			}
			if (strcmp(key->data.name,p->data.name)<0) { // 
				if (p == head) {// p ����� �̵��� ������ ���
					head = key; // head ������ ����
					p->link = key->link; // p->link�� key->link�� ����Ű�� ���� ����Ŵ
					key->link = p; // key->link�� p�� ����Ŵ���ν� ��� ��ȯ
				}else {// key���� p���� ��ȯ
					p->link = key->link; // p->link�� key->link�� ����Ű�� ���� ����Ŵ
					key->link = p; // key->link�� p�� ����Ŵ
					q->link = key; // q->link�� key�� ����Ŵ���ν� ��� ��ȯ					
				}
			}
		}
	}
	return head;
}
void display(ListNode* head)
{
	ListNode* p = head; // ���Ḯ��Ʈ ����
	printf("�� ��    ���� �� �� ��  ���� �� \n");
	printf("������������������������������������������������������\n");
	while (p != NULL) // ���Ḯ��Ʈ�� ������ �ݺ�
	{
		printf("�� %d  %s    %.1lf ��\n", p->data.number, p->data.name, p->data.total);
		p = p->link; // ��尪 �̵�
	}
	printf("������������������������������������������������������\n\n");
	printf("\n");

}
void FreeList(ListNode *head) {
	ListNode *p;
	while (head != NULL) {
		p = head;
		head = head->link;
		free(p);
		p = NULL;
	}
	printf("�޸� ���� �Ϸ�\n");
}
void main()
{
	FILE* fp = NULL; // ���� ������ ����
	ListNode* list = NULL; // ���Ḯ��Ʈ ����
	char buf[30]; // ���ڿ��� ���� ����
	student* stu, temp; // �����Ҵ��� ���� ����ü ����
	int count = 0; // ������ ������ ���� ������ �ľ��ϱ� ���� ����
	fp = fopen("data.txt", "r"); // data.txt������ �б� ���� ����
	if (fp == NULL) // ����ó��
	{
		printf("������ ���µ� �����߽��ϴ�.");
		exit(1);
	}
	while (!feof(fp)) // ������ ������ �˻�
	{
		fscanf(fp, "%d %s %lf", &temp.number, buf, &temp.total); 
		count++;
	}
	stu = (student*)malloc(sizeof(student) * count); // ������ ���� ��ŭ ����ü ���� �Ҵ�
	rewind(fp); // ���� ������ ����ġ
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d %s %lf", &stu[i].number, buf, &stu[i].total);
		int size = strlen(buf); // ���ڿ��� ���� �ľ�
		stu[i].name = (char*)malloc(sizeof(char) * (size + 1)); // ���ڿ� �����Ҵ�
		strcpy(stu[i].name, buf);

		list = insert_first(list, stu[i]); // ���Ḯ��Ʈ ����
	}	
	printf("======������ �����Ͱ�======\n");
	display(list);

	printf("======�������� �̸���======\n"); // �����ټ�
	list = InsertionSort(list,count);
	display(list);

	printf("======�������� �й���======\n"); // ���� ����
	list = bubble(list, count);
	display(list);

	printf("======�������� ������======\n"); // ���� ���� ��� ����
	list = SelectSort(list);
	display(list);

	FreeList(list);
	free(stu); // �޸� ����
	fclose(fp);
}