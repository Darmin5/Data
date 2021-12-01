#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef int SElemType;
typedef enum{NULL1,BASEOP,TURNNUM,BREAK};
typedef enum{NULL2,INIT,EMPTY,PUSH,POP};
typedef enum{NULL3,S,L};
/*1�����ʵ��ջ�����ִ洢�ṹ�еĻ���������ջ�ĳ�ʼ������ջ�ա���ջ����ջ�ȣ���
��2��Ӧ��ջ�Ļ���������ʵ������ת����������ƣ���
*/
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
	//printf("˳��ջ��ʼ���ɹ���\n");
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
	//printf("��ջ�ɹ���\n");
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base) {
	//printf("��ǰջΪ�գ�\n");
		return ERROR;
	}
	e = *--S.top;
	//printf("��ջ�ɹ�������Ԫ��Ϊ��%d\n",e);
	return OK;
}

Status StackEmpty(SqStack S) {
	//�ж�ջ��
	if (S.top == S.base) {
		//printf("��ǰջΪ�գ�\n");
		return OK;
	}
	//printf("��ǰջ��Ϊ�գ�\n");
	return ERROR;
}

//��ջ�Ĵ洢�ṹ
typedef struct LinkNode {
	SElemType data;
	struct LinkNode* next;
}LinkNode,*LinkStack;
//����Ϊ��ջ�Ļ�������
Status InitLinkStack(LinkStack &top) {
	//����һ����ջ
	top = (LinkStack)malloc(sizeof(LinkNode));
	if (!top) exit(OVERFLOW);
	top->next = NULL;		//����һ����㣬��Ϊջ�׽��
	//printf("��ջ��ʼ���ɹ���\n");
	return OK;
}
Status LinkPush(LinkStack& top, SElemType e) {
	//��ջ����ջ����
	LinkStack p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	if (!p) exit(ERROR);
	p->data = e;
	p->next = top;	//��Ϊջ���Ƚ�����Ľṹ������ջ��Ҫ��Ϊ��β
	top = p;
	//printf("��ջ�ɹ���\n");
	return OK;
}

Status LinkPop(LinkStack& top, SElemType& e) {
	//��ջ�ĳ�ջ����
	LinkStack p;		
	if (top->next == NULL)		//��top->next�ǿյĻ���˵��ջ��ֻ��ջ�׽�㣬��ջΪ��
		return ERROR;
	e = top->data;
	p = top;
	top = top->next;
	free(p);
	//printf("��ջ�ɹ�������Ԫ��Ϊ��%d\n",e);
	return OK;

}

Status LStackEmpty(LinkStack &top) {
	//�ж���ջ�Ƿ�Ϊ�գ�����OK������ERROR��
	if (top->next == NULL) {
		//printf("��ǰջΪ�գ�\n");
		return OK;
	}
	else //printf("��ǰջ��Ϊ�գ�\n");
	return ERROR;
}

void conversion(SElemType e) {
	//������һ���Ǹ�ʮ����������ӡ��������ֵ�İ˽�����
	SqStack SQ;
	InitStack(SQ);
	int n;
	while (e) {
		n = e % 8;
		Push(SQ, n);
		e = e / 8;
	}
	printf("ת����İ˽�����Ϊ��\n");
	while (!StackEmpty(SQ)) {
		Pop(SQ, n);
		printf("%d", n);
	}
	printf("\n");
}

int main() {
	SqStack Sq;
	LinkStack LS;
	Status a, b, c;
	SElemType e;
	while (TRUE) {
		system("cls");
		printf("��ѡ������ִ�еĲ�����\n1.ִ��ջ�Ļ�������\n2.��ʮ��������ת���ɰ˽���\n3.�˳�\n");
		scanf("%d", &a);
		switch (a) {
		case BASEOP:{
			printf("��ѡ��������еĻ���������\n1.ջ�ĳ�ʼ��\n2.�ж�ջ��\n3.��ջ\n4.��ջ\n");
			//printf("��ѡ���������:\n1.˳��ջ\n2.��ջ\n")��
			scanf("%d", &b);
			switch (b) {
			case INIT:printf("��ѡ���������:\n1.˳��ջ\n2.��ջ\n"); scanf("%d", &c); if (c == S)InitStack(Sq); else InitLinkStack(LS); break;
			case EMPTY:printf("��ѡ���������:\n1.˳��ջ\n2.��ջ\n"); scanf("%d", &c); if (c == S)StackEmpty(Sq); else LStackEmpty(LS); break;
			case PUSH:printf("������ѹջԪ�أ�\n"); scanf("%d", &e); printf("��ѡ���������:\n1.˳��ջ\n2.��ջ\n"); scanf("%d", &c); if (c == S)Push(Sq, e); else LinkPush(LS, e); break;
			case POP:printf("��ѡ���������:\n1.˳��ջ\n2.��ջ\n"); scanf("%d", &c); if (c == S)Pop(Sq, e); else LinkPop(LS, e); break;
			}
			break;
		}//case BASEOP
		case TURNNUM:printf("������һ���Ǹ�ʮ��������\n"); scanf("%d", &e);conversion(e); break;
		case BREAK:return 0;
		}//switch(a)
		system("pause");
	}
	return 0;
}
