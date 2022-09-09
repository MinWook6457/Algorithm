#include <stdio.h>
#include <string.h> // strcmp 함수 사용
#include <malloc.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct student {
	int number;
	char* name;
	double total;
}student;
typedef struct ListNode {
	student data;
	struct ListNode* link;
} ListNode;
ListNode* insert_first(ListNode* head, student st) // 노드 맨 앞에 삽입
{
	ListNode* p = (ListNode*)malloc(sizeof(ListNode));
	p->data = st;
	p->link = head;
	head = p;
	return head;
}

void display(ListNode* head)
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

ListNode* SelectSort(ListNode* head) {
	ListNode* p, *q, *r; // head : 기준 p : 탐색포인터 q : 최소값 r : q의 앞노드
	if (head->link == NULL) // 재귀함수 종료 조건 , 연결리스트의 head->link 값이 NULL인 경우 리스트 종료
		return;
	p = q = r = head; // p,q,r 초기화
	while (p != NULL) { // 연결리스트의 끝 까지 검사
		if (p->data.total > q->data.total) { // 앞 노드의 값이 더 큰 경우 노드 이동
			q = p;
		}
		p = p->link;
	}
	
	p = head; // 포인터 p 초기화
	while (p->link != NULL) { // 
		if (p->link == q) { // q가 이전 노드인 경우 즉, p의 데이터 값이 q의 데이터 값보다 작은경우
			r = p; // p의 값을 r에 저장
		}
		p = p->link; // p 이동
	}
	// 반복문이 끝나면 p는 가장 큰 데이터 값을 가리킴
	if (head != q) // head와 q의 값이 같다는 것은 리스트의 끝을 의미함
	{
		p->link = head; // p의 링크를 헤드가 가리키는 곳에 연결
		head = q; // 헤드값 변경
		r->link = NULL; // r은 마지막 노드이므로 NULL로 초기화
	}
	head->link = (SelectSort(head->link)); // 재귀함수 호출을 통해 head 포인터 변경시킴
	return head;
}
void main()
{
	FILE* fp = NULL;
	ListNode* list = NULL;
	char buf[30];
	student* stu, temp;
	int count = 0;
	fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		printf("파일을 여는데 실패했습니다.");
		exit(1);
	}
	while (!feof(fp))
	{
		fscanf(fp, "%d %s %lf", &temp.number, buf, &temp.total);
		count++;
	}
	stu = (student*)malloc(sizeof(student) * count);
	rewind(fp);
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d %s %lf", &stu[i].number, buf, &stu[i].total);
		int size = strlen(buf);
		stu[i].name = (char*)malloc(sizeof(char) * (size + 1));
		strcpy(stu[i].name, buf);
		printf("%d %s %lf\n", stu[i].number, stu[i].name, stu[i].total);
		list = insert_first(list, stu[i]);
	}
	list = SelectSort(list);
	printf("======선택정렬 학점순======\n");
	display(list);
	fclose(fp);
}