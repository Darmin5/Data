#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100

typedef int Status;
typedef char QElemType;
typedef enum { NULL1, BASEOP, BREAK };
typedef enum { NULL2, INIT, EMPTY, PUSH, POP };
typedef enum { NULL3, S, L };
/*（3）编程实现队列在两种存储结构中的基本操作（队列的初始化、判队列空、入队列、出队列）；
*/

//单链队列--队列的链式存储结构
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitLQueue(LinkQueue& Q) {
	//构造一个空队列Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	printf("单链队列初始化成功！\n");
	return OK;
}

Status DestroyLQueue(LinkQueue& Q) {
	//销毁队列
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	printf("销毁成功！\n");
	return OK;
}

Status EnLQueue(LinkQueue& Q, QElemType e) {
	//插入元素e为Q的新的队尾元素(入队)
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	printf("入队成功！\n");
	return OK;
}

Status DeLQueue(LinkQueue& Q, QElemType& e) {
	//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK（出队）
	//否则返回ERROR
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	printf("出队成功！出队元素是:%d\n",e);
	return OK;
}

Status EmptyLQueue(LinkQueue& Q) {
	//判断队列是否为空，空则返回OK，否则返回ERROR
	if (Q.front == Q.rear) {
		printf("该单链队列是空队列！\n");
		return OK;
	}
	printf("该单链队列不为空！\n");
	return ERROR;
}

//--------循环队列-队列的顺序存储结构--------
typedef struct {
	QElemType* base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue& Q) {
	//构造一个空队列
	Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	printf("循环队列初始化成功！\n");
	return OK;
}

int QueueLength(SqQueue Q) {
	//返回队列Q的元素个数，即队列的长度
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue& Q, QElemType e) {
	//插入e为Q的新的队尾元素
	if ((Q.rear + 1) % MAXQSIZE == Q.front)	return ERROR;	//队列满
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	printf("入队成功！\n");
	return OK;
}

Status DeQueue(SqQueue& Q, QElemType& e) {
	//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK
	//否则返回ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	printf("出队成功！出队元素是：%d\n", e);
	return OK;
}

Status EmptyQueue(SqQueue& Q) {
	//判断队列是否为空，若空则返回OK，否则返回ERROR
	if (Q.front == Q.rear) {
		printf("该单链队列是空队列！\n");
		return OK;
	}
	printf("该单链队列不为空！\n");
	return ERROR;
}


int main() {
	LinkQueue LS;
	SqQueue Sq;
	Status a, b, c;
	QElemType e;
	while (TRUE) {
		system("cls");
		printf("请选择你想执行的操作：\n1.执行队列的基本操作\n2.退出\n");
		scanf("%d", &a);
		switch (a) {
		case BASEOP: {
			printf("请选择你想进行的基本操作：\n1.队列的初始化\n2.判断队列空\n3.入队\n4.出队\n");
			//printf("请选择操作对象:\n1.循环队列（顺序结构队列）\n2.单链队列\n")；
			scanf("%d", &b);
			switch (b) {
			case INIT:printf("请选择操作对象:\n1.循环队列（顺序结构队列）\n2.单链队列\n"); scanf("%d", &c); if (c == S)InitQueue(Sq); else InitLQueue(LS); break;
			case EMPTY:printf("请选择操作对象:\n1.循环队列（顺序结构队列）\n2.单链队列\n"); scanf("%d", &c); if (c == S)EmptyQueue(Sq); else EmptyLQueue(LS); break;
			case PUSH:printf("请输入入队元素：\n"); scanf("%d", &e); printf("请选择操作对象:\n1.循环队列（顺序结构队列）\n2.单链队列\n"); scanf("%d", &c); if (c == S)EnQueue(Sq, e); else EnLQueue(LS, e); break;
			case POP:printf("请选择操作对象:\n1.循环队列（顺序结构队列）\n2.单链队列\n"); scanf("%d", &c); if (c == S)DeQueue(Sq, e); else DeLQueue(LS, e); break;
			}
			break;
		}//case BASEOP
		case BREAK:return 0;
		}//switch(a)
		system("pause");
	}
	return 0;
}
