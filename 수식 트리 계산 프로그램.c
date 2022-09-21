#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode n1 = { 1,NULL,NULL };
TreeNode n2 = { 4,NULL,NULL };
TreeNode n3 = { '*',&n1,&n2 };
TreeNode n4 = { 16, NULL , NULL };
TreeNode n5 = { 25, NULL , NULL };
TreeNode n6 = { '+',&n4, &n5 };
TreeNode n7 = { '+',&n3, &n6 };
TreeNode *exp = &n7;

int evaluate(TreeNode *root) {
	if (root == NULL) // 트리의 내용이 빈경우 종료 : 에러 검출 코드 반드시 필요!!
		return;
	if (root->left == NULL && root->right == NULL) // 트리의 마지막 노드인 경우
		return root->data;
	else {
		int op1 = evaluate(root->left); // 재귀 호출
		int op2 = evaluate(root->right); // 재귀 호출
		printf("%d %c %d을 계산합니다.\n", op1, root->data, op2);

		switch (root->data)
		{
		case '+':
			return op1 + op2;
		case '*':
			return op1 * op2;
		case '-':
			return op1 - op2;
		case '/':
			return op1 / op2;
		default:
			break;
		}
	}
	return 0;
}
void main() {
	printf("수식의 값은 %d입니다\n",evaluate(exp));

}