////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 : 2022년 09월 11일
// 프로그램명 : 파일입출력, 연결리스트, 동적할당, 정렬을 이용한 학생 데이터 정리
// 프로그램설명 : data.txt 파일에 학번, 이름, 총점이 저장되어있다. 
//				  정보를 동적 할당을 이용하여 단순 연결리스트로 입력 받아 저장하고, 
//				  연결리스트를이용하여 학번, 이름, 총점 순으로 정렬
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <time.h> // 시간 측정 함수
#include <string.h> // strcmp 함수 사용
#pragma warning(disable:4996)
typedef struct { // 구조체 선언
	int number; // 학번
	char *name; // 이름
	double total; // 총점
}student;

typedef struct ListNode { // 연결리스트 구조체 선언
	student data; // 노드의 데이터값
	struct ListNode *link; // 연결리스트 링크
} ListNode;
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 09월 11일
// 함수명 : insert_first()
// 함수설명 : 리스트의 시작 부분에 항목을 삽입하는 함수
// 함수입력: 헤드 포인터와 새롭게 추가되는 데이터
// 함수출력: 변경된 헤드 포인터
//			
////////////////////////////////////////////////////////////////
ListNode *insert_first(ListNode *head, student st) // 노드 맨 앞에 삽입
{
	ListNode *p = (ListNode *)malloc(sizeof(ListNode)); // 동적 메모리 할당을 통하여 새로운 노드 p 생성
	if (p == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	p->data = st; // p->data에 st 저장
	p->link = head; // 헤드 포인터의 값을 복사
	head = p; // 헤드 포인터 변경
	return head; // 변경된 헤드 포인터 반환
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 09월 11일
// 함수명 : bubble()
// 함수설명 : 버블 정렬 알고리즘을 이용하여 연결리스트의 링크값을 변경하여 정렬하는 함수
// 함수입력 : 헤드 포인터와 연결리스트 노드의 개수
// 함수출력 : 연결리스트를 학점에 따라 오름 차순으로 정렬하여 헤드포인터 변경
//			
////////////////////////////////////////////////////////////////
ListNode *bubble(ListNode *head, int n) // 성공한 코드!
{
	for (int i = 0; i < n; i++) {
		ListNode* current = head; // 현재노드가 헤드지정
		ListNode* next = current->link; // 현재노드의 링크가 가리키는 다음 노드를 가리킴
		ListNode* previous = NULL; // 이전노드의 초기값 설정 = NULL

		while (next != NULL) {
			if (current->data.number > next->data.number) { // 오름차순
				if (current == head) { // 현재노드가 head를 가리키고 next가 현재노드의 링크를 가리킬 때 next노드의 값이 큰 경우
					head = next; // 헤드 포인터 변경
				}
				else { // 이전 노드의 링크가 다음 노드를 가리킴
					previous->link = next;
				}
				current->link = next->link; // current->link 값을 next->link가 가리키는 값으로 변경
				next->link = current; // next->link가 current를 가리킴

				previous = next; // 이전 노드를 앞 노드가 가리키는 값으로 변경
				next = current->link; // current->link가 가리크는 값을 next가 가리키도록 변경
			}
			else {
				previous = current; // 이전 노드 값을 현재 노드가 가리키도록 변경
				current = current->link; // 현재 노드값 이동
				next = current->link; // 다음 노드값 이동
			}
		}
	}
	return head;
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 09월 11일
// 함수명 : SelectSort()
// 함수설명 : 선택 정렬 알고리즘을 이용하여 연결리스트의 링크값을 변경하여 정렬하는 재귀 함수
// 함수입력 : 헤드 포인터
// 함수출력 : 재귀 호출을 통하여 헤드 포인터의 링크 값을 반환하고 
//			  호출이 끝나면 변경된 헤드 포인터 반환		
////////////////////////////////////////////////////////////////
ListNode* SelectSort(ListNode* head) {
	ListNode* p, *q, *r; // head : 기준 , p : 탐색포인터 , q : 최소값 , r : q의 앞노드
	if (head->link == NULL) // 재귀함수 종료 조건 , 연결리스트의 head->link 값이 NULL인 경우 리스트 종료
		return;
	p = q = r = head; // p,q,r 초기화
	while (p != NULL) { // 연결리스트의 끝 까지 검사, 더 이상 q의 노드가 p의 노드보다 크지 않은경우 반복 종료
		if (p->data.total > q->data.total) { // 앞 노드의 값이 더 큰 경우 노드 이동
			q = p; // q노드가 p노드를 가리킴
		}
		p = p->link; // p이동 
	}

	p = head; // 포인터 p 초기화
	while (p->link != NULL) {
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
	head->link = (SelectSort(head->link)); // 재귀함수 호출을 통해 head 포인터 연결
	return head;
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 09월 11일
// 함수명 : insertionSortList()
// 함수설명 : 삽입 정렬 알고리즘을 이용하여 연결리스트의 링크값을 변경하고
//			  key->link 값을 반환하여 연결리스트 정렬
// 함수입력 : 헤드 포인터
// 함수출력 : 재귀 호출을 통하여 헤드 포인터의 링크 값을 반환하고 
//			  호출이 끝나면 변경된 헤드 포인터 반환		
////////////////////////////////////////////////////////////////
ListNode* insertionSortList(ListNode* head) { 
	ListNode *key = (ListNode *)malloc(sizeof(ListNode)); // 선택 정렬을 위한 key값 동적할당
	key->link = head; // key->link는 헤드 포인터를 가리킴
	ListNode *current = head, *previous = key; // prev = key값
	while (current !=NULL) { // 더이상 정렬할 값이 없는 경우 반복 종료
		if (current->link !=NULL && (strcmp(current->link->data.name, current->data.name))<0) { // 현재 노드와 다음 노드 비교, 오름차순
			while (previous->link != NULL && (strcmp(previous->link->data.name, current->link->data.name)) < 0) { // 현재 노드는 그대로 있고 previous노드를 옮겨가며 검사
				previous = previous->link; // previous 노드 이동
			}
			ListNode *temp = previous->link; // 노드를 교체하기위한 버퍼 
			previous->link = current->link;  // privous->link 값을 current->link가 가리키는 값으로 변경
			current->link = current->link->link; // current->link 값을 current->link->link를 통해 변경
			previous->link->link = temp; // previous->link->link 값을 temp가 가리키는 값으로 변경
			previous = key; // key는 head를 가리키고 있었으며 prev값을 head포인터로 변경 : key->link는 정렬된 head를 가리킴
		}
		else // 현재 노드 이동
			current = current->link;
	}
	return key->link; // key->link는 헤드 포인터를 가리킴
}
void display(ListNode* head)
{
	ListNode* p = head; // 연결리스트 복사
	printf("│ 학    번│ 이 름 │  총점 │ \n");
	printf("┣━━━━━━━━━┼━━━━━━━━┼━━━━━━┤\n");
	while (p != NULL) // 연결리스트의 끝까지 반복
	{
		printf("│ %d  %s    %.1lf │\n", p->data.number, p->data.name, p->data.total);
		p = p->link; // 노드값 이동
	}
	printf("└━━━━━━━━━┴━━━━━━━━┴━━━━━━┘\n\n");
	printf("\n");

}
void main()
{
	FILE* fp = NULL; // 파일 포인터 선언
	ListNode* list = NULL; // 연결리스트 선언
	char buf[30]; // 문자열을 담을 버퍼
	student* stu, temp; // 동적할당을 위한 구조체 선언
	int count = 0; // 파일의 데이터 값의 개수를 파악하기 위한 변수
	fp = fopen("data.txt", "r"); // data.txt파일을 읽기 모드로 열기
	if (fp == NULL) // 예외처리
	{
		printf("파일을 여는데 실패했습니다.");
		exit(1);
	}
	while (!feof(fp)) // 파일의 끝까지 검사
	{
		fscanf(fp, "%d %s %lf", &temp.number, buf, &temp.total); 
		count++;
	}
	stu = (student*)malloc(sizeof(student) * count); // 데이터 개수 만큼 구조체 동적 할당
	rewind(fp); // 파일 포인터 원위치
	for (int i = 0; i < count; i++)
	{
		fscanf(fp, "%d %s %lf", &stu[i].number, buf, &stu[i].total);
		int size = strlen(buf); // 문자열의 길이 파악
		stu[i].name = (char*)malloc(sizeof(char) * (size + 1)); // 문자열 동적할당
		strcpy(stu[i].name, buf);
		printf("%d %s %lf\n", stu[i].number, stu[i].name, stu[i].total);
		list = insert_first(list, stu[i]); // 연결리스트 삽입
	}	
	printf("======정렬전 데이터값======\n");
	display(list);

	printf("======버블정렬 학번순======\n"); // 선배 먼저
	list = bubble(list, count);
	display(list);

	printf("======삽입정렬 이름순======\n"); // 가나다순
	list = insertionSortList(list);
	display(list);

	printf("======선택정렬 학점순======\n"); // 학점 높은 사람 먼저
	list = SelectSort(list);
	display(list);




	free(stu); // 메모리 헤제
	fclose(fp);
}