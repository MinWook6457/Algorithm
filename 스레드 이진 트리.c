#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
	int is_thread; // ���� ������ ��ũ�� ������ �̸� true(�±� �ʵ���)
				   // is_thread�� true�̸� right�� ���� �ļ����̰� is_thread�� false�̸� ������ �ڽ��� ����Ű�� �����Ͱ� �ȴ�.
}TreeNode;

TreeNode N1 = { 'A',NULL,NULL ,1};
TreeNode N2 = { 'B',NULL,NULL ,1};
TreeNode N3 = { 'C',&N1,&N2 ,0};
TreeNode N4 = { 'D',NULL,NULL ,1};
TreeNode N5 = { 'E',NULL,NULL ,0};
TreeNode N6 = { 'F',&N4,&N5 ,0};
TreeNode N7 = { 'G',&N3,&N6 ,0};
TreeNode *exp = &N7;

TreeNode *find_succeesor(TreeNode *p) {
	TreeNode *q = p->right; // q�� p�� ������ ������
	if (q == NULL || p->is_thread == TRUE) // ���� ������ �����Ͱ� NULL�̰� �� �������̸� ������ ������ ��ȯ
		return q;

	while (q->left != NULL) // q�� ���� ���� ���� �̵�
		q = q->left;

	return q;
}

void thread_inorder(TreeNode *t) {
	TreeNode *q;

	q = t; // ��� ����
	while (q->left) // q�� ���� ���� ���� �̵�
		q = q->left;

	do {
		printf("%c ", q->data);
		q = find_succeesor(q);
	} while (q);
}

void main() {
	N1.right = &N3;
	N2.right = &N7;
	N4.right = &N6;

	thread_inorder(exp);
}