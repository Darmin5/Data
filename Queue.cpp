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
/*��3�����ʵ�ֶ��������ִ洢�ṹ�еĻ������������еĳ�ʼ�����ж��пա�����С������У���
*/

//��������--���е���ʽ�洢�ṹ
typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitLQueue(LinkQueue& Q) {
	//����һ���ն���Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	printf("�������г�ʼ���ɹ���\n");
	return OK;
}

Status DestroyLQueue(LinkQueue& Q) {
	//���ٶ���
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	printf("���ٳɹ���\n");
	return OK;
}

Status EnLQueue(LinkQueue& Q, QElemType e) {
	//����Ԫ��eΪQ���µĶ�βԪ��(���)
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	printf("��ӳɹ���\n");
	return OK;
}

Status DeLQueue(LinkQueue& Q, QElemType& e) {
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����ӣ�
	//���򷵻�ERROR
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	printf("���ӳɹ�������Ԫ����:%d\n",e);
	return OK;
}

Status EmptyLQueue(LinkQueue& Q) {
	//�ж϶����Ƿ�Ϊ�գ����򷵻�OK�����򷵻�ERROR
	if (Q.front == Q.rear) {
		printf("�õ��������ǿն��У�\n");
		return OK;
	}
	printf("�õ������в�Ϊ�գ�\n");
	return ERROR;
}

//--------ѭ������-���е�˳��洢�ṹ--------
typedef struct {
	QElemType* base;
	int front;
	int rear;
}SqQueue;

Status InitQueue(SqQueue& Q) {
	//����һ���ն���
	Q.base = (QElemType*)malloc(MAXQSIZE * sizeof(QElemType));
	if (!Q.base) exit(OVERFLOW);
	Q.front = Q.rear = 0;
	printf("ѭ�����г�ʼ���ɹ���\n");
	return OK;
}

int QueueLength(SqQueue Q) {
	//���ض���Q��Ԫ�ظ����������еĳ���
	return (Q.rear - Q.front + MAXQSIZE) % MAXQSIZE;
}

Status EnQueue(SqQueue& Q, QElemType e) {
	//����eΪQ���µĶ�βԪ��
	if ((Q.rear + 1) % MAXQSIZE == Q.front)	return ERROR;	//������
	Q.base[Q.rear] = e;
	Q.rear = (Q.rear + 1) % MAXQSIZE;
	printf("��ӳɹ���\n");
	return OK;
}

Status DeQueue(SqQueue& Q, QElemType& e) {
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK
	//���򷵻�ERROR
	if (Q.front == Q.rear) return ERROR;
	e = Q.base[Q.front];
	Q.front = (Q.front + 1) % MAXQSIZE;
	printf("���ӳɹ�������Ԫ���ǣ�%d\n", e);
	return OK;
}

Status EmptyQueue(SqQueue& Q) {
	//�ж϶����Ƿ�Ϊ�գ������򷵻�OK�����򷵻�ERROR
	if (Q.front == Q.rear) {
		printf("�õ��������ǿն��У�\n");
		return OK;
	}
	printf("�õ������в�Ϊ�գ�\n");
	return ERROR;
}


int main() {
	LinkQueue LS;
	SqQueue Sq;
	Status a, b, c;
	QElemType e;
	while (TRUE) {
		system("cls");
		printf("��ѡ������ִ�еĲ�����\n1.ִ�ж��еĻ�������\n2.�˳�\n");
		scanf("%d", &a);
		switch (a) {
		case BASEOP: {
			printf("��ѡ��������еĻ���������\n1.���еĳ�ʼ��\n2.�ж϶��п�\n3.���\n4.����\n");
			//printf("��ѡ���������:\n1.ѭ�����У�˳��ṹ���У�\n2.��������\n")��
			scanf("%d", &b);
			switch (b) {
			case INIT:printf("��ѡ���������:\n1.ѭ�����У�˳��ṹ���У�\n2.��������\n"); scanf("%d", &c); if (c == S)InitQueue(Sq); else InitLQueue(LS); break;
			case EMPTY:printf("��ѡ���������:\n1.ѭ�����У�˳��ṹ���У�\n2.��������\n"); scanf("%d", &c); if (c == S)EmptyQueue(Sq); else EmptyLQueue(LS); break;
			case PUSH:printf("���������Ԫ�أ�\n"); scanf("%d", &e); printf("��ѡ���������:\n1.ѭ�����У�˳��ṹ���У�\n2.��������\n"); scanf("%d", &c); if (c == S)EnQueue(Sq, e); else EnLQueue(LS, e); break;
			case POP:printf("��ѡ���������:\n1.ѭ�����У�˳��ṹ���У�\n2.��������\n"); scanf("%d", &c); if (c == S)DeQueue(Sq, e); else DeLQueue(LS, e); break;
			}
			break;
		}//case BASEOP
		case BREAK:return 0;
		}//switch(a)
		system("pause");
	}
	return 0;
}
