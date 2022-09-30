#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#pragma warning(disable:4996)
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;
typedef TreeNode* element;
typedef struct QueueNode // 연결리스트 큐 정의
{
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct Queue
{
	QueueNode* front, *rear;
}Queue;

void QueueInit(Queue* q) // 큐 초기화
{
	q->front = q->rear = NULL;
}
// 큐 공백 검사
int	is_empty(Queue* q)
{
	return q->front == NULL;
}
// 큐에 데이터 삽입
void enqueue(Queue* q, element data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->link = NULL;
	newNode->data = data;
	if (is_empty(q)) {
		q->front = newNode;
		q->rear = newNode;
	}
	else {
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

// 큐에서 데이터 삭제
void dequeue(Queue* q)
{
	QueueNode* pDelNode = q->front;
	q->front = q->front->link;	//	front를 다음 위치로 이동 : 연결리스트 이용
	free(pDelNode);
}
// 큐에 있는 모드 데이터 삭제
void DeleteAllNode(Queue* q)
{
	while (!is_empty(q))
		dequeue(q);
}
// 레벨순회
void LevelTraversal(TreeNode* pRoot)
{
	Queue q;
	TreeNode* p = NULL;

	QueueInit(&q);		// 큐를 초기화
	enqueue(&q, pRoot);	// 루트 노드를 큐에 저장
	while (!QueueIsEmpty(&q))
	{
		p = q.front->data;	// 노드 p가 q가 가지고 있는 데이터를 가리킴
		printf("%d ", p->data);
		if (p->left != NULL)
			enqueue(&q, p->left);
		if (p->right != NULL)
			enqueue(&q, p->right);

		dequeue(&q); // 큐에서 현재 노드를 제거
	}
	DeleteAllNode(&q);
}

TreeNode *newNode(int item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	temp->data = item;
	temp->left = temp->right = NULL;
	return temp;
}
// 재귀적인 삽입
TreeNode *insert_node_recurcive(TreeNode *node, int key) {
	if (node == NULL)
		return newNode(key);
	if (key < node->data)
		node->left = insert_node_recurcive(node->left, key);
	else
		node->right = insert_node_recurcive(node->right, key);
	return node;
}
// 반복적인 삽입
void insert_node(TreeNode **root, int item) {
	TreeNode* p, *t; // p는 t의 부모노드 t는 현재위치

	t = *root;
	p = NULL;

	while (t != NULL) {
		if (item == t->data) // 새로 추가하려는 단어가 이미 트리에 있는 경우
			return;
		p = t; // *** 부모 노드 업데이트 ***
		if (item < t->data)
			t = t->left;
		else
			t = t->right;
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	if (n == NULL) {
		fprintf(stderr, "메모리 할당 실패\n");
		exit(1);
	}
	n->data = item;
	//printf("%d ", n->data);
	n->left = n->right = NULL;

	if (p != NULL) {
		if (item < p->data)
			p->left = n;
		else
			p->right = n;
	}
	else {
		*root = n;
	}
}
void preorder(TreeNode* temp) { // 전위 순회
	if (temp != NULL) {
		printf("[%d] ", temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}
void inorder(TreeNode* temp) { // 중위 순회
	if (temp != NULL) {
		inorder(temp->left);
		printf("[%d] ", temp->data);
		inorder(temp->right);
	}
}
void postorder(TreeNode* temp) { // 후위 순회
	if (temp != NULL) {
		postorder(temp->left);
		postorder(temp->right);
		printf("[%d] ", temp->data);
	}
}
int get_height(TreeNode *node) { // 노드의 높이 구하는 함수
	if (node == NULL) {
		return 0;
	}
	int left_height = get_height(node->left);
	int right_height = get_height(node->right);
	return left_height > right_height ? left_height + 1 : right_height + 1;
}
void *delete_node(TreeNode *root) {//동적으로 할당된 노드들의 메모리를 반환하는 함수
	if (root != NULL) {
		delete_node(root->left);
		delete_node(root->right);
		free(root);
	}
}
int get_leaf_count(TreeNode *node) { // 단말 노드의 개수 구하는 함수
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL)
			return 1;
		else
			count = get_leaf_count(node->left) + get_leaf_count(node->right);
	}
	return count;
}
int get_node_count(TreeNode *node) { // 노드의 개수 구하는 함수
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
	FILE *fp;
	TreeNode *root1 = NULL;
	TreeNode *root2 = NULL;
	fp = fopen("data.txt", "r");
	int tmp;
	if (fp == NULL) {
		fprintf(stderr, "파일 열기 실패\n");
		exit(1);
	}
	start1 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		insert_node(&root1, tmp);
	}
	end1 = clock();
	printf("\n[삽입연산 반복방법시 걸린시간 : %f]\n", (float)(end1 - start1) / CLOCKS_PER_SEC);
	int h1 = get_height(root1);
	printf("Height = %d\n", h1);

	rewind(fp);
	
	start2 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		root2 = insert_node_recurcive(root2, tmp);
	}
	end2 = clock();
	printf("\n[삽입연산 순회방법시 걸린시간 : %f]\n", (float)(end2 - start2) / CLOCKS_PER_SEC);
	printf("\n");
	printf("트리의 높이 = %d, 단말 노드 개수 = %d 모든 노드 개수 = %d ", get_height(root1), get_leaf_count(root1), get_node_count(root1));
	

	/*
	start3 = clock();
	preorder(root1);
	end3 = clock();
	printf("\n[전위순회 걸린시간 : %f]\n", (float)(end3 - start3) / CLOCKS_PER_SEC);
	*/

	/*
	start4 = clock();
	inorder(root1);
	end4 = clock();
	printf("\n[중위순회 걸린시간 : %f]\n", (float)(end4 - start4) / CLOCKS_PER_SEC);
	*/

	/*
	start5 = clock();
	postorder(root1);
	end5 = clock();
	printf("\n[후위순회 걸린시간 : %f]\n", (float)(end5 - start5) / CLOCKS_PER_SEC);

	*/
	start6 = clock();
	LevelTraversal(root1);
	end6 = clock();
	printf("\n[레벨순회 걸린시간 : %f]\n", (float)(end6 - start6) / CLOCKS_PER_SEC);
	delete_node(root1); // 트리 노드 해제
	delete_node(root2); // 트리 노드 해제
	fclose(fp);
}