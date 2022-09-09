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
ListNode *insert_first(ListNode *head, student st) // 노드 맨 앞에 삽입
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = st;
	p->link = head;
	head = p;
	return head;
}

ListNode *bubble(ListNode *head, int n) // 성공한 코드!
{
	for (int i = 0; i < n; i++) {
		ListNode* current = head; // 현재노드가 헤드지정
		ListNode* next = current->link; // 현재노드의 링크가 가리키는 다음 노드를 가리킴
		ListNode* previous = NULL; // 이전노드의 초기값 설정 = NULL

		while (next != NULL) {
			if (current->data.total < next->data.total) { // 내림차순
				if (current == head) { // 현재노드가 head를 가리키고 next가 현재노드의 링크를 가리킬 때 next노드의 값이 큰 경우
					head = next; // 헤드 포인터 변경
				}
				else { // 이전 노드의 링크가 다음 노드를 가리킴
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
void bubble_sort_name(ListNode *head) { // 이름순 버블 정렬 strcmp 함수 사용
	ListNode *p, *q;
	student tmp;

	for (p = head;p != NULL;p = p->link) { // 노드 p는 머리노드 부터 검사
		for (q = p;q != NULL;q = q->link) { // q는 p노드를 따라감
			if (strcmp(p->data.name, q->data.name) > 0) { // q노드의 학번이 p노드의 학번보다 작은경우 swap
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
void main()
{
	FILE *fp = NULL;
	ListNode *list = NULL;
	student stu;
	int count = 0;
	fp = fopen("data.txt", "r");

	if (fp == NULL)
	{
		printf("파일을 여는데 실패했습니다.");
		exit(1);
	}

	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &stu.number, stu.name, &stu.total);
		count++;
		list = insert_first(list, stu);
	}
	printf("======정렬전 데이터값======\n");
	display(list);
	printf("======버블정렬 학점순======\n");
	list = bubble(list, count);
	display(list);
	//free(list1);
	fclose(fp);
}