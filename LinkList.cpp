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
typedef enum { NU,INIT,ADD ,INSERT, DELETE, SEARCH,SHOW,BREAK };
/*
���ʵ�����Ա���ʽ�洢�еĻ���������ʵ�֣����Ա�Ĵ��������롢ɾ���Ͳ��ҵȣ��������һ���˵��������Ա�Ļ���������
*/
//-----���Ա�ĵ�����洢�ṹ-----
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

Status InitList(LinkList &L) {
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    L->data = 0;
    printf("�����ʼ���ɹ���\n");
    return OK;

}
Status AddElem_L(LinkList &L, ElemType e) {
    //a�������ͷ�������������Ԫ��
    LinkList p;
    p = L;              //pָ��ͷ���
    LinkList s = (LinkList)malloc(sizeof(LNode));		//�����½��
    s->data = e;
    s->next = NULL;				//����L��
    if (p != NULL) {
        while (p->next)  p = p->next;
        p->next = s;
    }
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }
    printf("��ӳɹ���\n");
    return OK;
}

Status LocatePos(LinkList &L, int i, LinkList& p) {
    //����pָʾ��������l�е�i������λ�ò�����OK��iֵ���Ϸ�ʱ����ERROR
    //i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
    LinkList q;
    q = L;
    int len = 0;
    if (q != NULL) {
        q = q->next;
        while (q) {
            len++;
            if (len == i) {
                p = q;
            }
            q = q->next;
        }//while
        if (i<0 || i>len)return ERROR;
        else return OK;
    }//if
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }

}

Status ListInsert_L(LinkList& L, int i, ElemType e) {
    //�ڴ�ͷ���ĵ������Ա�L�ĵ�i��Ԫ��֮ǰ����Ԫ��e
    //i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
    LinkList h;
    if (!LocatePos(L, i - 1, h)) return ERROR;  //iֵ���Ϸ�
    LinkList p;
    p = L;
    if (p != NULL) {
        int j = 0;
        p = p->next;
        while (p) {
            j++;
            if (j == i - 1) {
                LinkList q = (LinkList)malloc(sizeof(LNode));
                q->data = e;
                q->next = p->next;
                p->next = q;
                printf("����ɹ���\n");
                return OK;
            }
            p = p->next;
        }
    }
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }
}

Status DeleteElem_L(LinkList &L,int i,ElemType &e) {
    //ɾ�������еĵ�i��Ԫ�أ�����e������ֵ
    LinkList h;
    LinkList p;
    p = L;
    if (!LocatePos(L, i - 1, h)) return ERROR;  //iֵ���Ϸ�
    if (p != NULL) {
        int j = 0;
        p = p->next;
        while (p) {
            j++;
            if (j == i - 1 ) {
                LinkList q = p->next;
                e = q->data;
                p->next = p->next->next;
                free(q);
                printf("ɾ���ɹ�����ɾ����Ԫ��Ϊ��%d\n",e);
                return OK;
            }
            p = p->next;
        }
    }
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }

}

Status LocateElem_L(LinkList &L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    //����ʽ���Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ�صĴ���
    //���ҵ����򷵻�����L�еĴ��򣬷��򷵻�0
    LinkList p;
    p = L;
    if (p != NULL) {
        int j = 0;
        p = p->next;
        while (p) {
            j++;
            if (compare(p->data, e)) {
                printf("���д��ڷ���������Ԫ�أ���һ������������Ԫ�صĴ���Ϊ��%d\n", j);
                return j;
            }
            p = p->next;
        }
        printf("����û�з���������Ԫ��!\n");
        return 0;
    }
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }
}

Status ShowElem_L(LinkList &L){
    //չʾ�����е�����Ԫ��
    LinkList p;
    p = L;
    if (p != NULL) {
        p = p->next;
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
    }//if'
    else {
        printf("������û�н��г�ʼ�������Ƚ�������ĳ�ʼ����\n");
        return ERROR;
    }
}

Status Compare(ElemType e1, ElemType e2) {
    if (e1 == e2)
        return OK;
    else
        return ERROR;
}

int main() {
    LinkList L;
    L = NULL;
    ElemType e;
    int i;
    Status c;
    while (TRUE) {
        system("cls");
        printf("������ʹ����ʽ���Ա���ѡ��Ըñ�Ĳ�����\n");
        printf("1.��ʼ������\n");
        printf("2.���β���Ԫ��\n");
        printf("3.�ڱ�L�е�i��λ��֮ǰ�����µ�Ԫ��\n");
        printf("4.�ڱ�L��ɾ����i��Ԫ��\n");
        printf("5.�ڱ�L�в���ĳԪ��\n");
        printf("6.չʾ����Ԫ��\n");
        printf("7.�˳�����\n");
        scanf("%d", &c);
        switch (c) {
        case INIT:InitList(L); break;
        case ADD:printf("��������Ҫ�����Ԫ�أ� "); scanf("%d", &e); AddElem_L(L, e); break;
        case INSERT:printf("��������Ҫ�����Ԫ�غͲ����λ�ã�"); scanf("%d%d", &e, &i); ListInsert_L(L, i, e); break;
        case DELETE:printf("��������Ҫɾ����Ԫ�صĴ���"); scanf("%d", &i); DeleteElem_L(L, i, e); break;
        case SEARCH:printf("��������Ҫ���ҵ�Ԫ�أ� "); scanf("%d", &e); LocateElem_L(L, e, Compare); break;
        case SHOW:printf("Ŀǰ���е�Ԫ����:\n"); ShowElem_L(L); break;
        case BREAK:return 0;
        }
        system("pause");

    }
    return 0;
    return 0;
}
