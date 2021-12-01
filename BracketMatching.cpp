#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef char SElemType;
typedef struct {		//˳��ջ�Ĵ洢�ṹ
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;
//����Ϊ˳��ջ�Ļ�������
Status InitStack(SqStack& S) {
	//����һ����ջ
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)	exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
//	printf("˳��ջ��ʼ���ɹ���\n");
	return OK;
}

Status Push(SqStack& S, SElemType e) {
	//����eΪ�µ�ջ��Ԫ��
	if (S.top - S.base >= S.stacksize) {	//ջ�������Ӵ洢�ռ�
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)	exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
//	printf("��ջ�ɹ���\n");
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base) {
//	printf("��ǰջΪ�գ�\n");
		return ERROR;
	}
	e = *--S.top;
//	printf("��ջ�ɹ�������Ԫ��Ϊ��%d\n",e);
	return OK;
}

Status StackEmpty(SqStack S) {
	//�ж�ջ��
	if (S.top == S.base) {
//		printf("��ǰջΪ�գ�\n");
		return OK;
	}
//	printf("��ǰջ��Ϊ�գ�\n");
	return ERROR;
}
Status Matching(char* exp) {
	int state = 1;
	int i = 0;
	SqStack S;
	SElemType e;
	InitStack(S);
	while (i < strlen(exp) && state) {
		switch (exp[i]) {
		case '(': {Push(S, exp[i]); i++; break;}
		case ')': {
			SElemType c = *(S.top-1);			//����Ҫע�����topָ�벢����ָ��ջ��Ԫ�أ�����ָ��ջ��Ԫ�ص�����һ�� 
			if ((!StackEmpty(S)) && (c == '(')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case ')'
		case '{': {Push(S, exp[i]); i++; break; }
		case '}': {
			SElemType c = *(S.top-1);
			if ((!StackEmpty(S)) && (c == '{')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case '}'
		case '[': {Push(S, exp[i]); i++; break; }
		case ']': {
			SElemType c = *(S.top-1); 
			if ((!StackEmpty(S)) && (c == '[')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case ']'
		}//switch
	}//while
	if (StackEmpty(S) && state) {
		printf("����ƥ��ɹ���\n");
		return OK;
	}
	else {
		printf("����ƥ��ʧ�ܣ�\n");
		return ERROR;
	}
}
int main() {
	char bracket[100];
	scanf("%s", bracket);
	int len = strlen(bracket);
	Matching(bracket);
	return 0;
}
