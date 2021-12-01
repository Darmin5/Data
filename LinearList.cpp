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
//-----���Ա�Ķ�̬����˳��洢�ṹ-----//
typedef struct {
	ElemType* elem;
	int length;
	int listsize;
}SqList;
Status InitList_Sq(SqList& L) {
	//����һ���յ����Ա�
	L.elem = (ElemType*)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
	return OK;
}
void ListShow_Sq(SqList &L){
	//����ǰ���Ա��е�Ԫ��չʾ����
	int i;
	for(i = 0;i<L.length; i++){
		printf("%d\n",L.elem[i]);
	} 

}
Status ListAdd_Sq(SqList& L, ElemType e) {
	//��˳�����Ա�β������µ�Ԫ��e
	if (L.length >= L.listsize) {
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);
		L.elem = newbase;						//�»�ַ
		L.listsize += LISTINCREMENT;
	}
	L.elem[L.length] = e;					//��β������e
	++L.length;									//����1
	printf("��ӳɹ���\n");
	return OK;
	
}
Status ListInsert_Sq(SqList& L, int i, ElemType e) {
	//��˳�����Ա�L�е�i��λ��֮ǰ�����µ�Ԫ��e
	//i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
	if (i<1 || i>L.length + 1){ printf("iֵ���Ϸ���"); return ERROR;}	//iֵ���Ϸ�
	if (L.length >= L.listsize) {				//��ǰ�洢�ռ����������ӷ���
		ElemType* newbase = (ElemType*)realloc(L.elem, (L.listsize + LISTINCREMENT) * sizeof(ElemType));
		if (!newbase)exit(OVERFLOW);			//�洢����ʧ��
		L.elem = newbase;						//�»�ַ
		L.listsize += LISTINCREMENT;			//���Ӵ洢����
	}
	ElemType* q;
	ElemType* p;
	q = &(L.elem[i - 1]);						//qΪ����λ��
	for (p = &(L.elem[L.length - 1]); p >= q;--p) *(p+1)=*p;//����λ�ü�֮���Ԫ��������
		*q =e;									//����e
		++L.length;								//����1
		printf("����ɹ���\n"); 
		return OK;
}
Status ListDelete_Sq(SqList& L, int i, ElemType& e) {
	//��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
	//i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)
	if (i<1 || i>L.length ){ printf("iֵ���Ϸ���"); return ERROR;}	//iֵ���Ϸ�
	ElemType* p;
	ElemType* q;
	p = &(L.elem[i - 1]);
	e = *p;
	q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)	*(p - 1) = *p;
	--L.length;
	printf("ɾ���ɹ�����ɾ����Ԫ���ǣ�%d\n",e);
	return OK;
}
Status Compare(ElemType e1, ElemType e2) {
	if (e1 == e2)
		return OK;
	else
		return ERROR;
}
int LocateElem_Sq(SqList L, ElemType e, Status(*compare)(ElemType, ElemType)) {
	//��˳�����Ա�L�в��ҵ�һ��ֵ��e����compare()��Ԫ�صĴ���
	//���ҵ����򷵻�����L�еĴ��򣬷��򷵻�0
	int i = 1;
	ElemType* p;
	p = L.elem;
	while (i <= L.length && !(*compare)(*p++, e)) ++i;
	if (i <= L.length) {
		printf("��Ҫ�ҵ�Ԫ�ش��ڣ��ڱ��е�λ��Ϊ:%d\n",i);
		return i;
	}
	else {
		printf("û���ҵ���Ԫ�أ�\n");
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
		printf("������ʹ��˳�����Ա���ѡ��Ըñ�Ĳ�����\n");
		printf("0.���β���Ԫ��\n");
		printf("1.�ڱ�L�е�i��λ��֮ǰ�����µ�Ԫ��\n");
		printf("2.�ڱ�L��ɾ����i��Ԫ��\n");
		printf("3.�ڱ�L�в���ĳԪ��\n");
		printf("4.չʾ����Ԫ��\n");
		printf("5.�˳�����\n");
		scanf("%d", &c);
		switch (c) {
		case ADD:printf("��������Ҫ�����Ԫ�أ� "); scanf("%d", &e); ListAdd_Sq(L, e); break;
		case INSERT:printf("��������Ҫ�����Ԫ�غͲ����λ�ã�"); scanf("%d%d", &e, &i); ListInsert_Sq(L, i, e); break;
		case DELETE:printf("��������Ҫɾ����Ԫ�صĴ���"); scanf("%d", &i); ListDelete_Sq(L, i,e); break;
		case LOCATE:printf("��������Ҫ���ҵ�Ԫ�أ� "); scanf("%d", &e); LocateElem_Sq(L, e, Compare); break;
		case SHOW:printf("Ŀǰ���е�Ԫ����:\n");ListShow_Sq(L);break;
		case BREAK:return 0;
		}
		system("pause");
	}
	return 0;
}
