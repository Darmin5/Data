#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
typedef enum { ADD, ADDLa, ADDLb,DELETE, SHOW, MERGE,BREAK };
/*��2������һ����Ԫ�ص�������ĵ�����L������д����ʵ�֣�
a����x�������к��Ա���L�������ԣ�
b��������ֵ����min��max֮��Ľ��ɾ����������L�������ԣ�
c����ѡ������������L���ò������
��3�����ʵ�ֽ�������Ԫ�ص�������ĵ�����ϲ�Ϊһ���µİ�Ԫ�ص����ĵ�����
*/
//-----���Ա�ĵ�����洢�ṹ-----
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
Status AddElem_L(LinkList L, ElemType e) {
    //a����x�������к��Ա���L�������ԣ�
    LinkList p;
    p = L;              //pָ��ͷ���
    while (p->next&& (e > p->next->data))  p = p->next;
    LinkList s = (LinkList)malloc(sizeof(LNode));		//�����½��
    s->data = e;
    s->next = p->next;				//����L��
    p->next = s;
    printf("��ӳɹ���\n");
    return OK;
}
Status DeleteMidElem_L(LinkList L) {
    //b��������ֵ����min��max֮��Ľ��ɾ����������L�������ԣ�
    //������Ϊ�ձ���Ȼ����������ֻ��һ��Ԫ�ػ�������Ԫ�أ�����ɾ����û���м�ֵ��
    LinkList p,q,s;
    int i = 0;      //������
    p = L;          //ָ��ͷ���
    if (p->next == NULL)   return ERROR;    //��Ϊ�ձ�����ERROR
    q = p;
    while (q->next) {   //���������鿴Ԫ�ظ���
        i++;
        q = q->next;
    }                 
    if (i <= 2)  return OK;
    q = p->next->next;    //qָ��ڶ������
    while (q->next != NULL) {
        s = q;
        q = q->next;
        p->next->next = q;
        free(s);
    }
    printf("ɾ���ɹ���\n");
    return OK;
}
Status ShowElem_L(LinkList L) {
    //չʾ�����е�����Ԫ��
    LinkList p;
    p = L->next;
    if (!p) {
        printf("Ŀǰ����û���κ�Ԫ�أ�\n");
        return ERROR;
    }
    printf("Ŀǰ���е�Ԫ����: ");
    while (p) {
        printf("%d  ", p->data);
        p = p->next;
    }
    printf("\n");
    return OK;
}
Status MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc) {
    //��3�����ʵ�ֽ�������Ԫ�ص�������ĵ�����ϲ�Ϊһ���µİ�Ԫ�ص����ĵ�����
    printf("����La, "); ShowElem_L(La);
    printf("����Lb, "); ShowElem_L(Lb);
    Lc = (LinkList)malloc(sizeof(LNode));
    Lc->data = 0;
    Lc->next = NULL;    //�����µ�����ͷLc
    LinkList pa, pb, pc, q;
    int a, b;
    pa = La->next;  pb = Lb->next; pc = Lc;
    while (pa && pb) {
        a = pa->data;   b = pb->data;
        if (a <= b) {
            q = pa;
            pa = pa->next;
            q->next = NULL;
            pc->next = q;
            pc = pc->next;
        }//if
        else {  //a>b
            q = pb;
            pb = pb->next;
            q->next = NULL;
            pc->next = q;
            pc = pc->next;
        }
    }//while
    if (pa)  pc->next = pa;
    else pc->next = pb;
    free(La);   free(Lb);
    printf("�ϲ��ɹ�������Lc, "); ShowElem_L(Lc);
    return OK;
}

int main() {
    LinkList p = (LinkList)malloc(sizeof(LNode));
    LinkList pa = (LinkList)malloc(sizeof(LNode));
    LinkList pb = (LinkList)malloc(sizeof(LNode));
    LinkList L = p;
    LinkList La = pa;
    LinkList Lb = pb;
    LinkList Lc;
    L->data = 0;
    L->next = NULL;
    La->data = 0;
    La->next = NULL;
    Lb->data = 0;
    Lb->next = NULL;
    ElemType e;
    int i;
    Status c;
    while (TRUE) {
        system("cls");
        printf("������ʹ�����Ա���ѡ��Ըñ�Ĳ�����\n");
        printf("0.���L���Ԫ��\n");
        printf("1.���La���Ԫ��\n");
        printf("2.���Lb���Ԫ��\n");
        printf("3.�ڵ�����L��,������ֵ����min��max֮��Ľ��ɾ��\n");
        printf("4.չʾ����Ԫ��\n");
        printf("5.��La��Lb�ϲ�������������(ѡ�øù��ܺ󽫲����ٶ�La��Lb�����κβ���)\n");
        printf("6.�˳�����\n");
        scanf("%d", &c);
        switch (c) {
        case ADD:printf("��������Ҫ��ӵ�Ԫ�أ� "); scanf("%d", &e); AddElem_L(L, e); break;
        case ADDLa:printf("��������Ҫ��ӵ�Ԫ�أ� "); scanf("%d", &e); AddElem_L(La, e); break;
        case DELETE:DeleteMidElem_L(L); break;
        case ADDLb:printf("��������Ҫ��ӵ�Ԫ�أ� "); scanf("%d", &e); AddElem_L(Lb, e); break;
        case SHOW: {
            printf("��ѡ��Ҫչʾ������\n1.��ͨ������\n2.����La��Lb\n");
            scanf("%d", &i);
            switch (i) {
            case 1:ShowElem_L(L); break;
            case 2:ShowElem_L(La); ShowElem_L(Lb); break;
            }
            break;
        }
        case MERGE:MergeList_L(La, Lb, Lc); break;
        case BREAK:return 0;
        }
        system("pause");

    }
    return 0;
}
