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
/*1）编程实现栈在两种存储结构中的基本操作（栈的初始化、判栈空、入栈、出栈等）；
（2）应用栈的基本操作，实现数制转换（任意进制）；
*/
typedef struct {		//顺序栈的存储结构
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;
//以下为顺序栈的基本操作
Status InitStack(SqStack& S) {
	//构造一个空栈
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)	exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	//printf("顺序栈初始化成功！\n");
	return OK;
}

Status Push(SqStack& S, SElemType e) {
	//插入e为新的栈顶元素
	if (S.top - S.base >= S.stacksize) {	//栈满，增加存储空间
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)	exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	//printf("入栈成功！\n");
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base) {
	//printf("当前栈为空！\n");
		return ERROR;
	}
	e = *--S.top;
	//printf("弹栈成功！弹出元素为：%d\n",e);
	return OK;
}

Status StackEmpty(SqStack S) {
	//判断栈空
	if (S.top == S.base) {
		//printf("当前栈为空！\n");
		return OK;
	}
	//printf("当前栈不为空！\n");
	return ERROR;
}

//链栈的存储结构
typedef struct LinkNode {
	SElemType data;
	struct LinkNode* next;
}LinkNode,*LinkStack;
//以下为链栈的基本操作
Status InitLinkStack(LinkStack &top) {
	//构造一个链栈
	top = (LinkStack)malloc(sizeof(LinkNode));
	if (!top) exit(OVERFLOW);
	top->next = NULL;		//设置一个结点，作为栈底结点
	//printf("链栈初始化成功！\n");
	return OK;
}
Status LinkPush(LinkStack& top, SElemType e) {
	//链栈的入栈操作
	LinkStack p;
	p = (LinkNode*)malloc(sizeof(LinkNode));
	if (!p) exit(ERROR);
	p->data = e;
	p->next = top;	//因为栈是先进后出的结构，所以栈顶要作为链尾
	top = p;
	//printf("入栈成功！\n");
	return OK;
}

Status LinkPop(LinkStack& top, SElemType& e) {
	//链栈的出栈操作
	LinkStack p;		
	if (top->next == NULL)		//若top->next是空的话，说明栈中只有栈底结点，即栈为空
		return ERROR;
	e = top->data;
	p = top;
	top = top->next;
	free(p);
	//printf("弹栈成功！弹出元素为：%d\n",e);
	return OK;

}

Status LStackEmpty(LinkStack &top) {
	//判断链栈是否为空，空则OK，否则ERROR；
	if (top->next == NULL) {
		//printf("当前栈为空！\n");
		return OK;
	}
	else //printf("当前栈不为空！\n");
	return ERROR;
}

void conversion(SElemType e) {
	//将任意一个非负十进制数，打印输出与其等值的八进制数
	SqStack SQ;
	InitStack(SQ);
	int n;
	while (e) {
		n = e % 8;
		Push(SQ, n);
		e = e / 8;
	}
	printf("转化后的八进制数为：\n");
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
		printf("请选择你想执行的操作：\n1.执行栈的基本操作\n2.将十进制数字转化成八进制\n3.退出\n");
		scanf("%d", &a);
		switch (a) {
		case BASEOP:{
			printf("请选择你想进行的基本操作：\n1.栈的初始化\n2.判断栈空\n3.入栈\n4.弹栈\n");
			//printf("请选择操作对象:\n1.顺序栈\n2.链栈\n")；
			scanf("%d", &b);
			switch (b) {
			case INIT:printf("请选择操作对象:\n1.顺序栈\n2.链栈\n"); scanf("%d", &c); if (c == S)InitStack(Sq); else InitLinkStack(LS); break;
			case EMPTY:printf("请选择操作对象:\n1.顺序栈\n2.链栈\n"); scanf("%d", &c); if (c == S)StackEmpty(Sq); else LStackEmpty(LS); break;
			case PUSH:printf("请输入压栈元素：\n"); scanf("%d", &e); printf("请选择操作对象:\n1.顺序栈\n2.链栈\n"); scanf("%d", &c); if (c == S)Push(Sq, e); else LinkPush(LS, e); break;
			case POP:printf("请选择操作对象:\n1.顺序栈\n2.链栈\n"); scanf("%d", &c); if (c == S)Pop(Sq, e); else LinkPop(LS, e); break;
			}
			break;
		}//case BASEOP
		case TURNNUM:printf("请输入一个非负十进制数：\n"); scanf("%d", &e);conversion(e); break;
		case BREAK:return 0;
		}//switch(a)
		system("pause");
	}
	return 0;
}
