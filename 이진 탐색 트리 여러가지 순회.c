////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 : 2022년 10월 04일
// 프로그램명 : 이진 탐색 트리를 다양한 방법을 사용하여 삽입, 순회하는 프로그램
// 프로그램설명 : data.txt 파일에 32500개의 정수형 데이터가 저장되어있다.
//				  데이터를 이진 탐색 트리를 반복,재귀를
//				  이용하여 삽입,순회 한다.
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> // 동적 할당을  위한 헤더파일 
#include <time.h> // 시간 측정을 위한 헤더파일
#pragma warning(disable:4996)
typedef struct TreeNode { // 트리 노드 구조체 정의
	int data;
	struct TreeNode *left, *right;
}TreeNode;
typedef TreeNode* element;
typedef struct StackNode { // 연결리스트 스택 정의
	element data;
	struct StackNode *link;
}StackNode;

typedef struct QueueNode // 연결리스트 큐 정의
{
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct { 
	StackNode *top; // 연결리스트 스택의 상단 포인터 설정, 단순 연결리스트의 헤드포인터와 같음
}Stack;

typedef struct Queue
{
	QueueNode* front, *rear;
}Queue;
void StackInit(Stack *s) { // 스택 초기화
	s->top = NULL;
}
void QueueInit(Queue* q) // 큐 초기화
{
	q->front = q->rear = NULL;
}
// 스택 공백 검사
int is_empty_stack(Stack *s) {
	return s->top == NULL;
}
// 큐 공백 검사
int	is_empty_Queue(Queue* q)
{
	return q->front == NULL;
}

////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : push()
// 함수설명 : 연결리스트 스택에 삽입하는 함수
// 함수입력: 현재 스택 위치를 가리키는 포인터와 삽입할 데이터
// 함수출력: 변경된 top 포인터
//			
////////////////////////////////////////////////////////////////
void push(StackNode **top, element x) 
{
	// 힙에 새로운 노드 할당
	StackNode *node = (StackNode *)malloc(sizeof(StackNode));

	// Stack(힙)이 가득 찼는지 확인
	// 가득 찬 상태에서 삽입 시 스택 오버플로우
	if (!node){
		fprintf(stderr,"메모리 할당 실패\n");
		exit(1);
	}
	node->data = x; // 할당된 노드에 데이터 설정

	// 새 노드의 링크가 현재를 가리키도록 설정
	// 리스트의 최상위 노드
	node->link = *top;
	
	*top = node; // 상단 포인터 업데이트
}

////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : peek()
// 함수설명 : 연결리스트 스택에서 현재 노드를 확인하는 함수
// 함수입력: 스택 노드 포인터
// 함수출력: 스택 포인터가 가리키는 값 반환
//			
////////////////////////////////////////////////////////////////
element peek(StackNode *top)
{
	// 빈 Stack 확인
	if (!is_empty_stack(top)) {
		return top->data; // 현재 스택 포인터가 가리키는 값 반환
	}
	else {
		fprintf(stderr, "스택이 비어 있음\n");
		exit(1);
	}
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : pop()
// 함수설명 : 연결리스트 스택에서 노드를 삭제하는 함수
// 함수입력: 스택 노드 이중포인터
// 함수출력: 이중 포인터를 이용하여 원본 포인터가 가리키는 값 변경
//			
////////////////////////////////////////////////////////////////
element pop(StackNode **top)
{
	StackNode *node;
	// 스택 언더플로우 확인
	if (*top == NULL)
	{
		fprintf(stderr,"스택 언더플로우 발생\n");
		exit(1);
	}
	element x = peek(*top); // 최상위 노드의 데이터를 기록
	node = *top; // 노드는 top포인터를 가리킴
	*top = (*top)->link; // 다음 노드를 가리키도록 top 포인터 업데이트
	free(node); // 할당된 메모리 해제
	return x;
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : inorderIterative()
// 함수설명 : 트리에서 반복적으로 스택을 이용하여 중위 순회를 수행하는 함수
// 함수입력: 스택 노드 포인터
// 함수출력: 트리를 중위 순회하여 데이터 출력
////////////////////////////////////////////////////////////////
void inorderIterative(TreeNode* root)
{
	Stack *s = (Stack *)malloc(sizeof(Stack)); // 스택 동적 할당
	StackInit(s); // 스택 초기화
    while (!is_empty_stack(s) || root != NULL) // 현재 노드가 null이고 Stack도 비어 있으면 종료
    {
        // 현재 노드가 존재하면 Stack에 푸시
        // 왼쪽 자식으로 이동
        if (root != NULL)
        {
			push(&s, root);
			root = root->left;
        }
        else {
            // 현재 노드가 null이면 Stack에서 요소를 팝
            // 출력하고 마지막으로 현재 노드를 오른쪽 자식으로 설정
			root = pop(&s);
			printf("%d ", root->data);
			root = root->right;
        }
    }
	free(s); // 할당한 스택 메모리 해제
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : enqueue()
// 함수설명 : 연결리스트 큐에서 새로운 노드를 삽입하는 함수
// 함수입력: 큐 포인터, 삽입할 데이터
// 함수출력: 연결리스트 큐를 이용하여 데이터 삽입 및 연결
////////////////////////////////////////////////////////////////
void enqueue(Queue* q, element data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	newNode->link = NULL;
	newNode->data = data;
	if (is_empty_Queue(q)) { // 큐에 노드가 없는 경우
		q->front = newNode; 
		q->rear = newNode;
	}
	else { // 큐에 노드가 존재하는 경우
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : dequeue()
// 함수설명 : 연결리스트 큐에서 노드를 삭제하는 함수
// 함수입력: 큐 포인터
////////////////////////////////////////////////////////////////
void dequeue(Queue* q)
{
	if (is_empty_Queue(q)) {// 공백상태
		fprintf(stderr, "큐가 비어있음\n");
		exit(1);
	}
	QueueNode* delete_node = q->front; // 삭제할 노드 설정
	if (delete_node == NULL) {
		fprintf(stderr, "삭제할 수 없습니다\n");
		exit(1);
	}
	q->front = q->front->link;	//	front를 다음 위치로 이동 : 연결리스트 이용
	free(delete_node);
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 01일
// 함수명 : LevelTraversal()
// 함수설명 : 연결리스트 큐를 이용하여 이진 트리 레벨 순회
// 함수입력: 이진 탐색 트리의 루트 노드
// 함수출력: 레벨 순회가 완료된 트리
////////////////////////////////////////////////////////////////
void LevelTraversal(TreeNode* root)
{
	Queue q;
	TreeNode* p = NULL;
	if (root == NULL)
		return;
	QueueInit(&q);		// 큐를 초기화
	enqueue(&q, root);	// 루트 노드를 큐에 저장
	while (!is_empty_Queue(&q)) // 공백검사
	{
		p = q.front->data;	// 노드 p가 q가 가지고 있는 데이터를 가리킴
		printf("%d ", p->data); // p는 q가 가리키는 곳을 가리키므로 data값 접근가능
		if (p->left != NULL) // 왼쪽 자식 큐에 삽입 
			enqueue(&q, p->left);
		if (p->right != NULL) // 오른쪽 자식 큐에 삽입
			enqueue(&q, p->right);
		dequeue(&q); // dequeue를 통해 q->front의 위치를 이동함
	}
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : newNode()
// 함수설명 : 이진 탐색 트리에 삽입될 노드를 정의하는 함수
// 함수입력: 삽입할 데이터
// 함수출력: 삽입된 노드
////////////////////////////////////////////////////////////////
TreeNode *newNode(int item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) { // 예외처리
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	temp->data = item;
	printf("%d ", temp->data);
	temp->left = temp->right = NULL;
	return temp;
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : insert_node_recurcive()
// 함수설명 : 이진 탐색 트리에 재귀적으로 노드를 삽입하는 함수
// 함수입력: 루트 노드 와 키 값
// 함수출력: 변경된 루트 포인터
////////////////////////////////////////////////////////////////
TreeNode *insert_node_recurcive(TreeNode *node, int key) {
	if (node == NULL) // 트리가 공백이면 새로운 노드 반환
		return newNode(key);
	if (key < node->data) // 키 값이 노드의 데이터보다 작으면 왼쪽 자식으로 이동
		node->left = insert_node_recurcive(node->left, key);
	else if(key > node->data)// 키 값이 노드의 데이터보다 크다면 오른쪽 자식으로 이동
		node->right = insert_node_recurcive(node->right, key);
	return node; // 변경된 루트 포인터 반환
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : insert_node()
// 함수설명 : 이진 탐색 트리에 반복적인 방법을 사용하여 노드를 삽입하는 함수
// 함수입력: 루트 노드를 가리키는 이중 포인터와 키 값
// 함수출력: 변경된 루트 포인터
////////////////////////////////////////////////////////////////
void insert_node(TreeNode **root, int item) {
	TreeNode* p, *t; // p는 t의 부모노드 t는 현재위치

	t = *root; // 현재 노드는 루트 노드를 가리킴
	p = NULL; // 부모 노드 초기화

	while (t != NULL) {
		if (item == t->data) // 새로 추가하려는 데이터가 이미 트리에 있는 경우
			return;
		p = t; // *** 부모 노드 업데이트 ***
		if (item < t->data) // 키 값이 현재 노드의 값보다 작다면
			t = t->left; // 왼쪽으로 이동
		else // 키 값이 현재 노드의 값보다 크다면
			t = t->right; // 오른쪽으로 이동
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode)); // 삽입할 노드 동적할당
	if (n == NULL) { // 예외처리
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	n->data = item;
	printf("%d ", n->data);
	n->left = n->right = NULL; // 삽입할 노드는 단말 노드 이므로 왼쪽 오른쪽 자식노드 NULL로 초기화
	// 부모노드 연결 설정
	if (p != NULL) { 
		if (item < p->data) // 키 값이 부모 노드보다 작다면
			p->left = n; // 왼쪽 자식으로 연결
		else
			p->right = n; // 오른쪽 자식으로 연결
	}
	else {
		*root = n; // 부모노드가 NULL인 경우는 트리가 공백인 경우이므로 추가한 노드를 *root가 가리킴
	}
}
void preorder(TreeNode* temp) { //전위 순회
	if (temp != NULL) {
		printf("%d ", temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}
void inorder(TreeNode* temp) { //중위 순회
	if (temp != NULL) {
		inorder(temp->left);
		printf("%d ", temp->data);
		inorder(temp->right);
	}
}
void postorder(TreeNode* temp) { //후위 순회
	if (temp != NULL) {
		postorder(temp->left);
		postorder(temp->right);
		printf("%d ", temp->data);
	}
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : get_height()
// 함수설명 : 각각의 서브트리에 대하여 순환호출하고 더 큰 값이 높이가 되는 함수
// 함수입력: 루트 노드
// 함수출력: 서브트리들의 반환값중에서 큰값을 구하여 반환
////////////////////////////////////////////////////////////////
int get_height(TreeNode *node) { 
	if (!node)
		return 0;
	int left_height = get_height(node->left); // 왼쪽 서브트리의 높이를 순환호출을 통해 얻는다.
	int right_height = get_height(node->right); // 같은 방법으로 오른쪽 서브트리의 높이를 얻는다.
	return left_height > right_height ? left_height + 1 : right_height + 1; // 둘 중 큰 값에 1을 더해 반환한다.
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : delete_node()
// 함수설명 : 사용되지 않는 이진 탐색 트리의 노드들을 후위 순회를 이용하여 방문하면서 메모리 해제하는 함수
// 함수입력: 루트 노드
// 함수출력: 사용되지 않는 이진 탐색 트리의 노드 메모리 해제
////////////////////////////////////////////////////////////////
void *delete_node(TreeNode *root) { //동적으로 할당된 노드들의 메모리를 반환하는 함수
	if (root != NULL) {
		delete_node(root->left);
		delete_node(root->right);
		free(root);
	}
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : get_leaf_count()
// 함수설명 : 단말 노드는 왼쪽 자식과 오른쪽 자식이 NULL인 노드이므로 두 조건을
//			  만족하는 경우 개수를 하나씩 증가시키면서 전체 단말 노드 개수를 구하는 함수
// 함수입력: 루트 노드
// 함수출력: 전체 단말 노드 개수
////////////////////////////////////////////////////////////////
int get_leaf_count(TreeNode *node) { 
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) 
			return 1;
		else // 비단말 노드 이면 각각의 서브트리에 순환 호출하여 반환값 더함
			count = get_leaf_count(node->left) + get_leaf_count(node->right); 
	}
	return count;
}
////////////////////////////////////////////////////////////////
// 작성자 : 20194024 김민욱
// 작성일 :  2022년 10월 02일
// 함수명 : get_node_count()
// 함수설명 : 노드가 NULL을 가리킬때 까지 각각 서브트리에 순환 호출하여 반환값을 더함
// 함수입력: 루트 노드
// 함수출력: 전체 노드 개수
////////////////////////////////////////////////////////////////
int get_node_count(TreeNode *node) { 
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}
void main() {
	clock_t start1, end1; // 반복 시간 측정을 위한 변수
	clock_t start2, end2; // 순환 시간 측정을 위한 변수
	clock_t start3, end3; // 전위 순회 시간 측정을 위한 변수
	clock_t start4, end4; // 중위 순회 시간 측정을 위한 변수
	clock_t start5, end5; // 후위 순회 시간 측정을 위한 변수
	clock_t start6, end6; // 레벨 순회 시간 측정을 위한 변수
	clock_t start7, end7; // 반복적 순회 시간 측정을 위한 변수
	FILE *fp; // 파일 포인터 선언
	TreeNode *root1 = NULL; // 트리 노드 초기화
	TreeNode *root2 = NULL; // 트리 노드 초기화
	fp = fopen("data.txt", "r");
	int tmp; // 파일에서 읽어오는 값을 저장할 변수
	if (fp == NULL) { // 예외처리
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	
	start1 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		insert_node(&root1, tmp); // 반복적 삽입
	}
	end1 = clock();
	rewind(fp);
	start2 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		root2 = insert_node_recurcive(root2, tmp); // 순환적 삽입
	}
	end2 = clock();
	printf("\n");

	start3 = clock();
	preorder(root1); // 전위순회
	end3 = clock();	
	
	start4 = clock();
	inorder(root1); // 중위순회
	end4 = clock();
	
	start5 = clock();
	postorder(root1); // 후위순회
	end5 = clock();
	
	start6 = clock();
	LevelTraversal(root1); // 레벨순회
	end6 = clock();

	start7 = clock();
	inorderIterative(root1); // 반복적 중위순회
	end7 = clock();
	// 출력문
	printf("\n[삽입연산 반복방법시 걸린시간 : %f]\n", (float)(end1 - start1) / CLOCKS_PER_SEC);
	printf("\n[삽입연산 순회방법시 걸린시간 : %f]\n", (float)(end2 - start2) / CLOCKS_PER_SEC);
	printf("트리의 높이 = %d, 단말 노드 개수 = %d 모든 노드 개수 = %d ", get_height(root1), get_leaf_count(root1), get_node_count(root1));
	printf("\n[전위순회 걸린시간 : %f]\n", (float)(end3 - start3) / CLOCKS_PER_SEC);
	printf("\n[중위순회 걸린시간 : %f]\n", (float)(end4 - start4) / CLOCKS_PER_SEC);
	printf("\n[후위순회 걸린시간 : %f]\n", (float)(end5 - start5) / CLOCKS_PER_SEC);
	printf("\n[레벨순회 걸린시간 : %f]\n", (float)(end6 - start6) / CLOCKS_PER_SEC);
	printf("\n[반복적순회 걸린시간 : %f]\n", (float)(end7 - start7) / CLOCKS_PER_SEC);

	delete_node(root1); // 트리 노드 해제
	delete_node(root2); // 트리 노드 해제
	fclose(fp); // 파일 닫기
}