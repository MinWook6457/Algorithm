#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
	int is_thread; // 만약 오른쪽 링크가 스레드 이면 true(태그 필드임)
				   // is_thread가 true이면 right는 중위 후속자이고 is_thread가 false이면 오른쪽 자식을 가리키는 포인터가 된다.
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
	TreeNode *q = p->right; // q는 p의 오른쪽 포인터
	if (q == NULL || p->is_thread == TRUE) // 만약 오른쪽 포인터가 NULL이거 나 스레드이면 오른쪽 포인터 반환
		return q;

	while (q->left != NULL) // q를 가장 왼쪽 노드로 이동
		q = q->left;

	return q;
}

void thread_inorder(TreeNode *t) {
	TreeNode *q;

	q = t; // 노드 복사
	while (q->left) // q를 가장 왼쪽 노드로 이동
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