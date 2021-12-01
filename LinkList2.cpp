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
/*（2）建立一个按元素递增有序的单链表L，并编写程序实现：
a）将x插入其中后仍保持L的有序性；
b）将数据值介于min和max之间的结点删除，并保持L的有序性；
c）（选做）将单链表L逆置并输出；
（3）编程实现将两个按元素递增有序的单链表合并为一个新的按元素递增的单链表。
*/
//-----线性表的单链表存储结构-----
typedef struct LNode {
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
Status AddElem_L(LinkList L, ElemType e) {
    //a）将x插入其中后仍保持L的有序性；
    LinkList p;
    p = L;              //p指向头结点
    while (p->next&& (e > p->next->data))  p = p->next;
    LinkList s = (LinkList)malloc(sizeof(LNode));		//生成新结点
    s->data = e;
    s->next = p->next;				//插入L中
    p->next = s;
    printf("添加成功！\n");
    return OK;
}
Status DeleteMidElem_L(LinkList L) {
    //b）将数据值介于min和max之间的结点删除，并保持L的有序性；
    //若链表为空表，显然错误；若链表只有一个元素或者两个元素，则不用删除（没有中间值）
    LinkList p,q,s;
    int i = 0;      //计数器
    p = L;          //指向头结点
    if (p->next == NULL)   return ERROR;    //若为空表，返回ERROR
    q = p;
    while (q->next) {   //遍历链表，查看元素个数
        i++;
        q = q->next;
    }                 
    if (i <= 2)  return OK;
    q = p->next->next;    //q指向第二个结点
    while (q->next != NULL) {
        s = q;
        q = q->next;
        p->next->next = q;
        free(s);
    }
    printf("删除成功！\n");
    return OK;
}
Status ShowElem_L(LinkList L) {
    //展示链表中的所有元素
    LinkList p;
    p = L->next;
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
}
Status MergeList_L(LinkList& La, LinkList& Lb, LinkList& Lc) {
    //（3）编程实现将两个按元素递增有序的单链表合并为一个新的按元素递增的单链表。
    printf("对于La, "); ShowElem_L(La);
    printf("对于Lb, "); ShowElem_L(Lb);
    Lc = (LinkList)malloc(sizeof(LNode));
    Lc->data = 0;
    Lc->next = NULL;    //创立新的链表头Lc
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
    printf("合并成功！对于Lc, "); ShowElem_L(Lc);
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
        printf("你正在使用线性表，请选择对该表的操作：\n");
        printf("0.向表L添加元素\n");
        printf("1.向表La添加元素\n");
        printf("2.向表Lb添加元素\n");
        printf("3.在单链表L中,将数据值介于min和max之间的结点删除\n");
        printf("4.展示表中元素\n");
        printf("5.将La和Lb合并，并保持有序(选用该功能后将不能再对La和Lb进行任何操作)\n");
        printf("6.退出操作\n");
        scanf("%d", &c);
        switch (c) {
        case ADD:printf("请输入你要添加的元素： "); scanf("%d", &e); AddElem_L(L, e); break;
        case ADDLa:printf("请输入你要添加的元素： "); scanf("%d", &e); AddElem_L(La, e); break;
        case DELETE:DeleteMidElem_L(L); break;
        case ADDLb:printf("请输入你要添加的元素： "); scanf("%d", &e); AddElem_L(Lb, e); break;
        case SHOW: {
            printf("请选择要展示的链表：\n1.普通单链表\n2.链表La和Lb\n");
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
