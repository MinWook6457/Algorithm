////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� : 2022�� 10�� 04��
// ���α׷��� : ���� Ž�� Ʈ���� �پ��� ����� ����Ͽ� ����, ��ȸ�ϴ� ���α׷�
// ���α׷����� : data.txt ���Ͽ� 32500���� ������ �����Ͱ� ����Ǿ��ִ�.
//				  �����͸� ���� Ž�� Ʈ���� �ݺ�,��͸�
//				  �̿��Ͽ� ����,��ȸ �Ѵ�.
////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h> // ���� �Ҵ���  ���� ������� 
#include <time.h> // �ð� ������ ���� �������
#pragma warning(disable:4996)
typedef struct TreeNode { // Ʈ�� ��� ����ü ����
	int data;
	struct TreeNode *left, *right;
}TreeNode;
typedef TreeNode* element;
typedef struct StackNode { // ���Ḯ��Ʈ ���� ����
	element data;
	struct StackNode *link;
}StackNode;

typedef struct QueueNode // ���Ḯ��Ʈ ť ����
{
	element data;
	struct QueueNode* link;
}QueueNode;

typedef struct { 
	StackNode *top; // ���Ḯ��Ʈ ������ ��� ������ ����, �ܼ� ���Ḯ��Ʈ�� ��������Ϳ� ����
}Stack;

typedef struct Queue
{
	QueueNode* front, *rear;
}Queue;
void StackInit(Stack *s) { // ���� �ʱ�ȭ
	s->top = NULL;
}
void QueueInit(Queue* q) // ť �ʱ�ȭ
{
	q->front = q->rear = NULL;
}
// ���� ���� �˻�
int is_empty_stack(Stack *s) {
	return s->top == NULL;
}
// ť ���� �˻�
int	is_empty_Queue(Queue* q)
{
	return q->front == NULL;
}

////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : push()
// �Լ����� : ���Ḯ��Ʈ ���ÿ� �����ϴ� �Լ�
// �Լ��Է�: ���� ���� ��ġ�� ����Ű�� �����Ϳ� ������ ������
// �Լ����: ����� top ������
//			
////////////////////////////////////////////////////////////////
void push(StackNode **top, element x) 
{
	// ���� ���ο� ��� �Ҵ�
	StackNode *node = (StackNode *)malloc(sizeof(StackNode));

	// Stack(��)�� ���� á���� Ȯ��
	// ���� �� ���¿��� ���� �� ���� �����÷ο�
	if (!node){
		fprintf(stderr,"�޸� �Ҵ� ����\n");
		exit(1);
	}
	node->data = x; // �Ҵ�� ��忡 ������ ����

	// �� ����� ��ũ�� ���縦 ����Ű���� ����
	// ����Ʈ�� �ֻ��� ���
	node->link = *top;
	
	*top = node; // ��� ������ ������Ʈ
}

////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : peek()
// �Լ����� : ���Ḯ��Ʈ ���ÿ��� ���� ��带 Ȯ���ϴ� �Լ�
// �Լ��Է�: ���� ��� ������
// �Լ����: ���� �����Ͱ� ����Ű�� �� ��ȯ
//			
////////////////////////////////////////////////////////////////
element peek(StackNode *top)
{
	// �� Stack Ȯ��
	if (!is_empty_stack(top)) {
		return top->data; // ���� ���� �����Ͱ� ����Ű�� �� ��ȯ
	}
	else {
		fprintf(stderr, "������ ��� ����\n");
		exit(1);
	}
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : pop()
// �Լ����� : ���Ḯ��Ʈ ���ÿ��� ��带 �����ϴ� �Լ�
// �Լ��Է�: ���� ��� ����������
// �Լ����: ���� �����͸� �̿��Ͽ� ���� �����Ͱ� ����Ű�� �� ����
//			
////////////////////////////////////////////////////////////////
element pop(StackNode **top)
{
	StackNode *node;
	// ���� ����÷ο� Ȯ��
	if (*top == NULL)
	{
		fprintf(stderr,"���� ����÷ο� �߻�\n");
		exit(1);
	}
	element x = peek(*top); // �ֻ��� ����� �����͸� ���
	node = *top; // ���� top�����͸� ����Ŵ
	*top = (*top)->link; // ���� ��带 ����Ű���� top ������ ������Ʈ
	free(node); // �Ҵ�� �޸� ����
	return x;
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : inorderIterative()
// �Լ����� : Ʈ������ �ݺ������� ������ �̿��Ͽ� ���� ��ȸ�� �����ϴ� �Լ�
// �Լ��Է�: ���� ��� ������
// �Լ����: Ʈ���� ���� ��ȸ�Ͽ� ������ ���
////////////////////////////////////////////////////////////////
void inorderIterative(TreeNode* root)
{
	Stack *s = (Stack *)malloc(sizeof(Stack)); // ���� ���� �Ҵ�
	StackInit(s); // ���� �ʱ�ȭ
    while (!is_empty_stack(s) || root != NULL) // ���� ��尡 null�̰� Stack�� ��� ������ ����
    {
        // ���� ��尡 �����ϸ� Stack�� Ǫ��
        // ���� �ڽ����� �̵�
        if (root != NULL)
        {
			push(&s, root);
			root = root->left;
        }
        else {
            // ���� ��尡 null�̸� Stack���� ��Ҹ� ��
            // ����ϰ� ���������� ���� ��带 ������ �ڽ����� ����
			root = pop(&s);
			printf("%d ", root->data);
			root = root->right;
        }
    }
	free(s); // �Ҵ��� ���� �޸� ����
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : enqueue()
// �Լ����� : ���Ḯ��Ʈ ť���� ���ο� ��带 �����ϴ� �Լ�
// �Լ��Է�: ť ������, ������ ������
// �Լ����: ���Ḯ��Ʈ ť�� �̿��Ͽ� ������ ���� �� ����
////////////////////////////////////////////////////////////////
void enqueue(Queue* q, element data)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	if (newNode == NULL) {
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	newNode->link = NULL;
	newNode->data = data;
	if (is_empty_Queue(q)) { // ť�� ��尡 ���� ���
		q->front = newNode; 
		q->rear = newNode;
	}
	else { // ť�� ��尡 �����ϴ� ���
		q->rear->link = newNode;
		q->rear = newNode;
	}
}

////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : dequeue()
// �Լ����� : ���Ḯ��Ʈ ť���� ��带 �����ϴ� �Լ�
// �Լ��Է�: ť ������
////////////////////////////////////////////////////////////////
void dequeue(Queue* q)
{
	if (is_empty_Queue(q)) {// �������
		fprintf(stderr, "ť�� �������\n");
		exit(1);
	}
	QueueNode* delete_node = q->front; // ������ ��� ����
	if (delete_node == NULL) {
		fprintf(stderr, "������ �� �����ϴ�\n");
		exit(1);
	}
	q->front = q->front->link;	//	front�� ���� ��ġ�� �̵� : ���Ḯ��Ʈ �̿�
	free(delete_node);
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 01��
// �Լ��� : LevelTraversal()
// �Լ����� : ���Ḯ��Ʈ ť�� �̿��Ͽ� ���� Ʈ�� ���� ��ȸ
// �Լ��Է�: ���� Ž�� Ʈ���� ��Ʈ ���
// �Լ����: ���� ��ȸ�� �Ϸ�� Ʈ��
////////////////////////////////////////////////////////////////
void LevelTraversal(TreeNode* root)
{
	Queue q;
	TreeNode* p = NULL;
	if (root == NULL)
		return;
	QueueInit(&q);		// ť�� �ʱ�ȭ
	enqueue(&q, root);	// ��Ʈ ��带 ť�� ����
	while (!is_empty_Queue(&q)) // ����˻�
	{
		p = q.front->data;	// ��� p�� q�� ������ �ִ� �����͸� ����Ŵ
		printf("%d ", p->data); // p�� q�� ����Ű�� ���� ����Ű�Ƿ� data�� ���ٰ���
		if (p->left != NULL) // ���� �ڽ� ť�� ���� 
			enqueue(&q, p->left);
		if (p->right != NULL) // ������ �ڽ� ť�� ����
			enqueue(&q, p->right);
		dequeue(&q); // dequeue�� ���� q->front�� ��ġ�� �̵���
	}
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : newNode()
// �Լ����� : ���� Ž�� Ʈ���� ���Ե� ��带 �����ϴ� �Լ�
// �Լ��Է�: ������ ������
// �Լ����: ���Ե� ���
////////////////////////////////////////////////////////////////
TreeNode *newNode(int item) {
	TreeNode *temp = (TreeNode*)malloc(sizeof(TreeNode));
	if (temp == NULL) { // ����ó��
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	temp->data = item;
	printf("%d ", temp->data);
	temp->left = temp->right = NULL;
	return temp;
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : insert_node_recurcive()
// �Լ����� : ���� Ž�� Ʈ���� ��������� ��带 �����ϴ� �Լ�
// �Լ��Է�: ��Ʈ ��� �� Ű ��
// �Լ����: ����� ��Ʈ ������
////////////////////////////////////////////////////////////////
TreeNode *insert_node_recurcive(TreeNode *node, int key) {
	if (node == NULL) // Ʈ���� �����̸� ���ο� ��� ��ȯ
		return newNode(key);
	if (key < node->data) // Ű ���� ����� �����ͺ��� ������ ���� �ڽ����� �̵�
		node->left = insert_node_recurcive(node->left, key);
	else if(key > node->data)// Ű ���� ����� �����ͺ��� ũ�ٸ� ������ �ڽ����� �̵�
		node->right = insert_node_recurcive(node->right, key);
	return node; // ����� ��Ʈ ������ ��ȯ
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : insert_node()
// �Լ����� : ���� Ž�� Ʈ���� �ݺ����� ����� ����Ͽ� ��带 �����ϴ� �Լ�
// �Լ��Է�: ��Ʈ ��带 ����Ű�� ���� �����Ϳ� Ű ��
// �Լ����: ����� ��Ʈ ������
////////////////////////////////////////////////////////////////
void insert_node(TreeNode **root, int item) {
	TreeNode* p, *t; // p�� t�� �θ��� t�� ������ġ

	t = *root; // ���� ���� ��Ʈ ��带 ����Ŵ
	p = NULL; // �θ� ��� �ʱ�ȭ

	while (t != NULL) {
		if (item == t->data) // ���� �߰��Ϸ��� �����Ͱ� �̹� Ʈ���� �ִ� ���
			return;
		p = t; // *** �θ� ��� ������Ʈ ***
		if (item < t->data) // Ű ���� ���� ����� ������ �۴ٸ�
			t = t->left; // �������� �̵�
		else // Ű ���� ���� ����� ������ ũ�ٸ�
			t = t->right; // ���������� �̵�
	}
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode)); // ������ ��� �����Ҵ�
	if (n == NULL) { // ����ó��
		fprintf(stderr, "�޸� �Ҵ� ����\n");
		exit(1);
	}
	n->data = item;
	printf("%d ", n->data);
	n->left = n->right = NULL; // ������ ���� �ܸ� ��� �̹Ƿ� ���� ������ �ڽĳ�� NULL�� �ʱ�ȭ
	// �θ��� ���� ����
	if (p != NULL) { 
		if (item < p->data) // Ű ���� �θ� ��庸�� �۴ٸ�
			p->left = n; // ���� �ڽ����� ����
		else
			p->right = n; // ������ �ڽ����� ����
	}
	else {
		*root = n; // �θ��尡 NULL�� ���� Ʈ���� ������ ����̹Ƿ� �߰��� ��带 *root�� ����Ŵ
	}
}
void preorder(TreeNode* temp) { //���� ��ȸ
	if (temp != NULL) {
		printf("%d ", temp->data);
		preorder(temp->left);
		preorder(temp->right);
	}
}
void inorder(TreeNode* temp) { //���� ��ȸ
	if (temp != NULL) {
		inorder(temp->left);
		printf("%d ", temp->data);
		inorder(temp->right);
	}
}
void postorder(TreeNode* temp) { //���� ��ȸ
	if (temp != NULL) {
		postorder(temp->left);
		postorder(temp->right);
		printf("%d ", temp->data);
	}
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : get_height()
// �Լ����� : ������ ����Ʈ���� ���Ͽ� ��ȯȣ���ϰ� �� ū ���� ���̰� �Ǵ� �Լ�
// �Լ��Է�: ��Ʈ ���
// �Լ����: ����Ʈ������ ��ȯ���߿��� ū���� ���Ͽ� ��ȯ
////////////////////////////////////////////////////////////////
int get_height(TreeNode *node) { 
	if (!node)
		return 0;
	int left_height = get_height(node->left); // ���� ����Ʈ���� ���̸� ��ȯȣ���� ���� ��´�.
	int right_height = get_height(node->right); // ���� ������� ������ ����Ʈ���� ���̸� ��´�.
	return left_height > right_height ? left_height + 1 : right_height + 1; // �� �� ū ���� 1�� ���� ��ȯ�Ѵ�.
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : delete_node()
// �Լ����� : ������ �ʴ� ���� Ž�� Ʈ���� ������ ���� ��ȸ�� �̿��Ͽ� �湮�ϸ鼭 �޸� �����ϴ� �Լ�
// �Լ��Է�: ��Ʈ ���
// �Լ����: ������ �ʴ� ���� Ž�� Ʈ���� ��� �޸� ����
////////////////////////////////////////////////////////////////
void *delete_node(TreeNode *root) { //�������� �Ҵ�� ������ �޸𸮸� ��ȯ�ϴ� �Լ�
	if (root != NULL) {
		delete_node(root->left);
		delete_node(root->right);
		free(root);
	}
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : get_leaf_count()
// �Լ����� : �ܸ� ���� ���� �ڽİ� ������ �ڽ��� NULL�� ����̹Ƿ� �� ������
//			  �����ϴ� ��� ������ �ϳ��� ������Ű�鼭 ��ü �ܸ� ��� ������ ���ϴ� �Լ�
// �Լ��Է�: ��Ʈ ���
// �Լ����: ��ü �ܸ� ��� ����
////////////////////////////////////////////////////////////////
int get_leaf_count(TreeNode *node) { 
	int count = 0;

	if (node != NULL) {
		if (node->left == NULL && node->right == NULL) 
			return 1;
		else // ��ܸ� ��� �̸� ������ ����Ʈ���� ��ȯ ȣ���Ͽ� ��ȯ�� ����
			count = get_leaf_count(node->left) + get_leaf_count(node->right); 
	}
	return count;
}
////////////////////////////////////////////////////////////////
// �ۼ��� : 20194024 ��ο�
// �ۼ��� :  2022�� 10�� 02��
// �Լ��� : get_node_count()
// �Լ����� : ��尡 NULL�� ����ų�� ���� ���� ����Ʈ���� ��ȯ ȣ���Ͽ� ��ȯ���� ����
// �Լ��Է�: ��Ʈ ���
// �Լ����: ��ü ��� ����
////////////////////////////////////////////////////////////////
int get_node_count(TreeNode *node) { 
	int count = 0;
	if (node != NULL)
		count = 1 + get_node_count(node->left) + get_node_count(node->right);
	return count;
}
void main() {
	clock_t start1, end1; // �ݺ� �ð� ������ ���� ����
	clock_t start2, end2; // ��ȯ �ð� ������ ���� ����
	clock_t start3, end3; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start4, end4; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start5, end5; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start6, end6; // ���� ��ȸ �ð� ������ ���� ����
	clock_t start7, end7; // �ݺ��� ��ȸ �ð� ������ ���� ����
	FILE *fp; // ���� ������ ����
	TreeNode *root1 = NULL; // Ʈ�� ��� �ʱ�ȭ
	TreeNode *root2 = NULL; // Ʈ�� ��� �ʱ�ȭ
	fp = fopen("data.txt", "r");
	int tmp; // ���Ͽ��� �о���� ���� ������ ����
	if (fp == NULL) { // ����ó��
		fprintf(stderr, "���� ���� ����\n");
		exit(1);
	}
	
	start1 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		insert_node(&root1, tmp); // �ݺ��� ����
	}
	end1 = clock();
	rewind(fp);
	start2 = clock();
	while (!feof(fp)) {
		fscanf(fp, "%d ", &tmp);
		root2 = insert_node_recurcive(root2, tmp); // ��ȯ�� ����
	}
	end2 = clock();
	printf("\n");

	start3 = clock();
	preorder(root1); // ������ȸ
	end3 = clock();	
	
	start4 = clock();
	inorder(root1); // ������ȸ
	end4 = clock();
	
	start5 = clock();
	postorder(root1); // ������ȸ
	end5 = clock();
	
	start6 = clock();
	LevelTraversal(root1); // ������ȸ
	end6 = clock();

	start7 = clock();
	inorderIterative(root1); // �ݺ��� ������ȸ
	end7 = clock();
	// ��¹�
	printf("\n[���Կ��� �ݺ������ �ɸ��ð� : %f]\n", (float)(end1 - start1) / CLOCKS_PER_SEC);
	printf("\n[���Կ��� ��ȸ����� �ɸ��ð� : %f]\n", (float)(end2 - start2) / CLOCKS_PER_SEC);
	printf("Ʈ���� ���� = %d, �ܸ� ��� ���� = %d ��� ��� ���� = %d ", get_height(root1), get_leaf_count(root1), get_node_count(root1));
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end3 - start3) / CLOCKS_PER_SEC);
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end4 - start4) / CLOCKS_PER_SEC);
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end5 - start5) / CLOCKS_PER_SEC);
	printf("\n[������ȸ �ɸ��ð� : %f]\n", (float)(end6 - start6) / CLOCKS_PER_SEC);
	printf("\n[�ݺ�����ȸ �ɸ��ð� : %f]\n", (float)(end7 - start7) / CLOCKS_PER_SEC);

	delete_node(root1); // Ʈ�� ��� ����
	delete_node(root2); // Ʈ�� ��� ����
	fclose(fp); // ���� �ݱ�
}