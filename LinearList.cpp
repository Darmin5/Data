#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef int Status;
typedef int ElemType;
typedef enum {ADD,INSERT,DELETE,LOCATE,SHOW,BREAK};
//-----线性表的动态分配顺序存储结构-----//
typedef struct {
	ElemType* elem;
	int length;
	int listsize;
}SqList;
Status InitList_Sq(SqList& L) {
	//构造一个空的线性表
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
void ListShow_Sq(SqList &L){
	//将当前线性表中的元素展示出来
	int i;
	for(i = 0;i<L.length; i++){
		printf("%d\n",L.elem[i]);
	} 

}
Status ListAdd_Sq(SqList& L, ElemType e) {
	//在顺序线性表尾部添加新的元素e
	if (L.length >= L.listsize) {
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);
		L.elem = newbase;						//新基址
		L.listsize += LISTINCREMENT;
	}
	L.elem[L.length] = e;					//在尾部增加e
	++L.length;									//表长增1
	printf("添加成功！\n");
	return OK;
	
}
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	//在顺序线性表L中第i个位置之前插入新的元素e
	//i的合法值为1<=i<=ListLength_Sq(L)+1
	if (i<1 || i>L.length + 1){ printf("i值不合法！"); return ERROR;}	//i值不合法
	if (L.length >= L.listsize) {				//当前存储空间已满，增加分配
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);			//存储分配失败
		L.elem = newbase;						//新基址
		L.listsize += LISTINCREMENT;			//增加存储容量
	}
	ElemType* q;
	ElemType* p;
	q = &(L.elem[i - 1]);						//q为插入位置
	for (p = &(L.elem[L.length - 1]); p >= q;--p) *(p+1)=*p;//插入位置及之后的元素往后移
		*q =e;									//插入e
		++L.length;								//表长增1
		printf("插入成功！\n"); 
		return OK;
}
Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	//在顺序线性表L中删除第i个元素，并用e返回其值
	//i的合法值为1<=i<=ListLength_Sq(L)
	if (i<1 || i>L.length ){ printf("i值不合法！"); return ERROR;}	//i值不合法
	ElemType* p;
	ElemType* q;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)	*(p - 1) = *p;
	--L.length;
	printf("删除成功！你删除的元素是：%d\n",e);
	return OK;
}
Status Compare(ElemType e1, ElemType e2) {
	if (e1 == e2)
		return OK;
	else
		return ERROR;
}
int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	//在顺序线性表L中查找第一个值与e满足compare()的元素的次序
	//若找到，则返回其在L中的次序，否则返回0
	int i = 1;
	ElemType* p;
	p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) {
		printf("你要找的元素存在！在表中的位置为:%d\n",i);
		return i;
	}
	else {
		printf("没有找到该元素！\n");
		return 0;
	}
}
int main() {
	SqList L;
	ElemType e;
	int i;
	Status c;
	InitList_Sq(L);
	while (TRUE) {
		system("cls");
		printf("你正在使用顺序线性表，请选择对该表的操作：\n");
		printf("0.向表尾添加元素\n");
		printf("1.在表L中第i个位置之前插入新的元素\n");
		printf("2.在表L中删除第i个元素\n");
		printf("3.在表L中查找某元素\n");
		printf("4.展示表中元素\n");
		printf("5.退出操作\n");
		scanf("%d", &c);
		switch (c) {
		case ADD:printf("请输入你要插入的元素： "); scanf("%d", &e); ListAdd_Sq(L, e); break;
		case INSERT:printf("请输入你要插入的元素和插入的位置："); scanf("%d%d", &e, &i); ListInsert_Sq(L, i, e); break;
		case DELETE:printf("请输入你要删除的元素的次序："); scanf("%d", &i); ListDelete_Sq(L, i,e); break;
		case LOCATE:printf("请输入你要查找的元素： "); scanf("%d", &e); LocateElem_Sq(L, e, Compare); break;
		case SHOW:printf("目前表中的元素有:\n");ListShow_Sq(L);break;
		case BREAK:return 0;
		}
		system("pause");
	}
	return 0;
}
