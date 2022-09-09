////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 : 2022년 09월 06일
// 프로그램명 : 파일입출력, 연결리스트, 동적할당, 정렬을 이용한 학생 데이터 정리
// 프로그램설명 : data.txt 파일에 학번, 이름, 총점이 저장되어있다. 
//				  정보를 동적 할당을 이용하여 단순 연결리스트로 입력 받아 저장하고, 
//				  연결리스트를이용하여 학번, 이름, 총점 순으로 정렬
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h> // strcmp 함수 사용
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
ListNode *inser_first(ListNode *head, student st) // 노드 맨 앞에 삽입
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = st;
	p->link = head;
	head = p;
	return head;

}
ListNode *bubble_sort_grade(ListNode *head) { // 성적순 버블 정렬
	ListNode *p, *q, *r; 

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (q->data.total > p->data.total) { // q의 총점이 p의 총점보다 큰 경우 swap
				r = p->data; // p노드의 데이터를 버퍼에 저장
				p->data = q->data; // q데이터를 p데이터에 삽입
				q->data = r; // 버퍼에 있던 p노드의 데이터를 q노드에 삽입
			}
		}
	}
	return r;
}
/*
void bubble_sort_grade(ListNode *head) { // 성적순 버블 정렬
	ListNode *p, *q;
	student tmp; // 노드의 데이터를 바꾸기 위한 버퍼

	for (p = head;p != NULL;p = p->link) {
		for (q = p;q != NULL;q = q->link) {
			if (q->data.total > p->data.total) { // q의 총점이 p의 총점보다 큰 경우 swap
				tmp = p->data; // p노드의 데이터를 버퍼에 저장
				p->data = q->data; // q데이터를 p데이터에 삽입
				q->data = tmp; // 버퍼에 있던 p노드의 데이터를 q노드에 삽입
			}
		}
	}
}
*/
ListNode  *bubble_sort_number(ListNode *head) { // 학번순 버블 정렬
	ListNode *p, *q, *r;

	for (p = head;p != NULL;p = p->link) { // 노드 p는 머리노드 부터 검사
		for (q = p;q != NULL;q = q->link) { // q는 p노드를 따라감
			if (q->data.number < p->data.number) { // q노드의 학번이 p노드의 학번보다 작은경우 swap
				r = p->data;
				p->data = q->data;
				q->data = r;
			}
		}
	}
	return r;
}

ListNode *bubble_sort_name(ListNode *head) { // 이름순 버블 정렬 strcmp 함수 사용
	ListNode *p, *q, *r;

	for (p = head;p != NULL;p = p->link) { // 노드 p는 머리노드 부터 검사
		for (q = p;q != NULL;q = q->link) { // q는 p노드를 따라감
			if (strcmp(p->data.name,q->data.name)>	0) { // q노드의 학번이 p노드의 학번보다 작은경우 swap
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
	ListNode* p = head; // 연결리스트 복사
	printf("│ 학    번│ 이 름 │  총점 │ \n");
	printf("┣━━━━━━━━━┼━━━━━━━━┼━━━━━━┤\n");
	while (p != NULL)
	{
		printf("│ %d  %s    %.1lf │\n", p->data.number, p->data.name, p->data.total);
		p = p->link;
	}
	printf("└━━━━━━━━━┴━━━━━━━━┴━━━━━━┘\n\n");
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
void main()
{
	FILE *fp = NULL;
	ListNode *list = NULL;
	student stu;

	fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("파일을 여는데 실패했습니다.");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &stu.number, stu.name, &stu.total);
		printf("%d %s %.1lf\n", stu.number, stu.name, stu.total);
		list = inser_first(list, stu);
		// insert_node(&list, NULL, create_node(stu, NULL)); // 삽입과 동시에 새로운 노드 생성
	}
	printf("======버블정렬 학점순======\n");
	bubble_sort_grade(list);
	display(list);
	printf("======버블정렬 학번순======\n");
	bubble_sort_number(list);
	display(list);
	printf("======버블정렬 이름순======\n");
	bubble_sort_name(list);
	display(list);
	//free(list1);
	fclose(fp);
}