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
	if (*phead == NULL) { // 공백 연결리스트 인경우
		new_node->link = NULL; // 공백 리스트 첫 노드의 링크값 초기화
		*phead = new_node; // 리스트 헤드에 저장
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
	printf("┌━━━━━━━━━┬━━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━┬━━━━━━━━┐\n");
	printf("│ 학    번│ 이 름 │ 수학 │ 영어 │ 국어 │ 총점 │ 평  균 │\n");
	printf("├━━━━━━━━━┼━━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━┼━━━━━━━━┤\n");
	while (p != NULL)
	{ 
		printf("  %d  %s  %d     %d     %d    %d    %lf\n", p->data.hak, p->data.name, p->data.mat, p->data.eng, p->data.kor, p->data.tot, p->data.avg);
		p = p->link;
	}
	printf("└━━━━━━━━━┴━━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━┴━━━━━━━━┘\n\n");
	printf("\n");

}
ListNode *create_node(student data, ListNode *link)
{
	ListNode* new_node = (ListNode *)malloc(sizeof(ListNode));
	if (new_node == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
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
			if (q->data.tot > p->data.tot) { // q의 총점이 p의 총점보다 큰 경우 swap
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
		printf("파일을 여는데 실패했습니다.");
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