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
编程实现线性表链式存储中的基本操作的实现（线性表的创建、插入、删除和查找等），并设计一个菜单调用线性表的基本操作。
*/
//-----线性表的单链表存储结构-----
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;

Status InitList(LinkList &L) {
    L = (LinkList)malloc(sizeof(LNode));
    if (!L) exit(OVERFLOW);
    L->next = NULL;
    L->data = 0;
    printf("链表初始化成功！\n");
    return OK;

}
Status AddElem_L(LinkList &L, ElemType e) {
    //a）向带有头结点的链表中添加元素
    LinkList p;
    p = L;              //p指向头结点
    LinkList s = (LinkList)malloc(sizeof(LNode));		//生成新结点
    s->data = e;
    s->next = NULL;				//插入L中
    if (p != NULL) {
        while (p->next)  p = p->next;
        p->next = s;
    }
    else {
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
        return ERROR;
    }
    printf("添加成功！\n");
    return OK;
}

Status LocatePos(LinkList &L, int i, LinkList& p) {
    //返回p指示线性链表l中第i个结点的位置并返回OK，i值不合法时返回ERROR
    //i的合法值为1<=i<=ListLength_Sq(L)+1
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
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
        return ERROR;
    }

}

Status ListInsert_L(LinkList& L, int i, ElemType e) {
    //在带头结点的单链线性表L的第i个元素之前插入元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
    LinkList h;
    if (!LocatePos(L, i - 1, h)) return ERROR;  //i值不合法
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
                printf("插入成功！\n");
                return OK;
            }
            p = p->next;
        }
    }
    else {
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
        return ERROR;
    }
}

Status DeleteElem_L(LinkList &L,int i,ElemType &e) {
    //删除链表中的第i个元素，并用e返回其值
    LinkList h;
    LinkList p;
    p = L;
    if (!LocatePos(L, i - 1, h)) return ERROR;  //i值不合法
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
                printf("删除成功！被删除的元素为：%d\n",e);
                return OK;
            }
            p = p->next;
        }
    }
    else {
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
        return ERROR;
    }

}

Status LocateElem_L(LinkList &L, ElemType e, Status(*compare)(ElemType, ElemType)) {
    //在链式线性表L中查找第一个值与e满足compare()的元素的次序
    //若找到，则返回其在L中的次序，否则返回0
    LinkList p;
    p = L;
    if (p != NULL) {
        int j = 0;
        p = p->next;
        while (p) {
            j++;
            if (compare(p->data, e)) {
                printf("表中存在符合条件的元素！第一个满足条件的元素的次序为：%d\n", j);
                return j;
            }
            p = p->next;
        }
        printf("表中没有符合条件的元素!\n");
        return 0;
    }
    else {
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
        return ERROR;
    }
}

Status ShowElem_L(LinkList &L){
    //展示链表中的所有元素
    LinkList p;
    p = L;
    if (p != NULL) {
        p = p->next;
        if (!p) {
            printf("目前表中没有任何元素！\n");
            return ERROR;
        }
        printf("目前表中的元素有: ");
        while (p) {
            printf("%d  ", p->data);
            p = p->next;
        }
        printf("\n");
        return OK;
    }//if'
    else {
        printf("该链表还没有进行初始化！请先进行链表的初始化！\n");
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
        printf("你正在使用链式线性表，请选择对该表的操作：\n");
        printf("1.初始化链表\n");
        printf("2.向表尾添加元素\n");
        printf("3.在表L中第i个位置之前插入新的元素\n");
        printf("4.在表L中删除第i个元素\n");
        printf("5.在表L中查找某元素\n");
        printf("6.展示表中元素\n");
        printf("7.退出操作\n");
        scanf("%d", &c);
        switch (c) {
        case INIT:InitList(L); break;
        case ADD:printf("请输入你要插入的元素： "); scanf("%d", &e); AddElem_L(L, e); break;
        case INSERT:printf("请输入你要插入的元素和插入的位置："); scanf("%d%d", &e, &i); ListInsert_L(L, i, e); break;
        case DELETE:printf("请输入你要删除的元素的次序："); scanf("%d", &i); DeleteElem_L(L, i, e); break;
        case SEARCH:printf("请输入你要查找的元素： "); scanf("%d", &e); LocateElem_L(L, e, Compare); break;
        case SHOW:printf("目前表中的元素有:\n"); ShowElem_L(L); break;
        case BREAK:return 0;
        }
        system("pause");

    }
    return 0;
    return 0;
}
