#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
#define MAXSIZE 100
typedef int Status;
typedef int KeyType;
typedef char RecordType;
int number = 0, Sumlen = 0;
typedef struct ElemType {		//����/�����ݵ�����
	RecordType record;			//��¼
	KeyType key;				//�ؼ���
}ElemType;

typedef struct {				//˳�������
	ElemType r[MAXSIZE + 1];	//r[0]����
	int length;					//˳�����
}SqList;
/*
��1�����ʵ��һ�ֲ����㷨�����۰���ҡ������������Ĳ��ҡ���ϣ���ҵȣ�����������Ӧ��ASL��
��2�����ʵ��һ���ڲ������㷨����������򡢿�������ȣ���
*/
//--------------------------------------�����������Ĳ���----------------------------------------
//��������Ĵ洢�ṹ
typedef struct BiTNode { // ���ṹ
	ElemType data;
	int SL;
	struct BiTNode* lchild, * rchild;
	// ���Һ���ָ��
} BiTNode, * BiTree;

Status CreateBiTree(BiTree& T) {
	//�����������ֶ��������������
	char ch;
	int key;
	//printf("��������Ĺؼ��֣�\n");
	scanf("%d", &key);
	//getchar();
	//printf("��������ļ�¼��\n");
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data.record = ch; // ���ɸ���� 
		T->data.key = key;
		CreateBiTree(T->lchild); // ���������� 
		CreateBiTree(T->rchild); // ���������� 
	}
	return OK;
} // CreateBiTree

Status SearchBST(BiTree T, KeyType key,BiTree f, BiTree& p) {
	// �ڸ�ָ�� T ��ָ�����������еݹ�ز�����ؼ��ֵ���key ������Ԫ�أ������ҳɹ���
	// �򷵻�ָ�� p ָ�������Ԫ�صĽ�㣬�����غ���ֵΪTRUE;����������Ҳ��ɹ�������
	// ָ�� p ָ�����·���Ϸ��ʵ����һ����㣬�����غ���ֵΪFALSE, ָ�� f ָ��ǰ����
	// �Ľ���˫�ף����ʼ����ֵΪNULL
	if (!T) {
		p = f;
		printf("����ʧ�ܣ�ԭ��������û�д����Ԫ�أ�\n");
		return FALSE;
	} // ���Ҳ��ɹ�
	else if (key == T->data.key){
		p = T; 
		if (f != NULL) {
			printf("���ҳɹ�������Ԫ����ԭ�������У��丸ĸ���Ĺؼ���Ϊ��%d, ��¼Ϊ:%c\n", f->data.key, f->data.record);
		}
		else {
			printf("���ҳɹ�������Ԫ����ԭ�������У����� ���ڽڵ�Ϊ�����\n");
		}
		return TRUE; 
	} // ���ҳɹ�
	else if (key < T->data.key)
		SearchBST(T->lchild, key, T, p);	// ���������м�������
	else									
		SearchBST(T->rchild, key, T, p);	// ���������м�������
} //SearchBST

Status InsertBST(BiTree& T, ElemType e) {
	// �������������в����ڹؼ��ֵ��� e.key ������Ԫ��ʱ������Ԫ��ֵΪ e �Ľ�㣬������ TRUE; 
	// ���򣬲����в��벢����FALSE
	BiTree s,p;
	if (!SearchBST(T, e.key, NULL, p)) {
		s = (BiTree)malloc(sizeof(BiTNode));			// Ϊ�½�����ռ�
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p) T = s;									// ���� s Ϊ�µĸ����
		else if (e.key < p->data.key)
			p->lchild = s;								// ���� *s Ϊ *p ������
		else 
			p->rchild = s;								// ���� *s Ϊ *p ���Һ���
		printf("�ɹ���������ԭ�������У��½��ĸ�ĸ���Ĺؼ���Ϊ��%d, ��¼Ϊ:%c\n",p->data.key,p->data.record);
		return TRUE;									// ����ɹ�
	}
	else return FALSE;
} // Insert BST

Status GetSL(BiTree& T, BiTree& p) {
	//�������������������ÿ���������������
	if (T) {
		if (p != NULL)	T->SL = p->SL + 1;
		else  T->SL = 1;
		GetSL(T->lchild, T);	//����������
		GetSL(T->rchild, T);	//����������
	}
	return OK;
}

Status Callength(BiTree& T) {
	//������������������������Ľ�����������������
	if (T) {
		number++;
		Sumlen += T->SL;
		Callength(T->lchild);	//����������
		Callength(T->rchild);	//����������
	}
	return OK;
}

//-----------------------------------------��������------------------------------------------
int Partition(ElemType R[], int low, int high) {
	R[0] = R[low]; 
	KeyType pivotkey;
	pivotkey = R[low].key; // ����
	while (low < high) {
		while (low < high && R[high].key >= pivotkey)
			--high; // ������������
		R[low] = R[high];
		while (low < high && R[low].key <= pivotkey)
			++low; // ������������
		R[high] = R[low];
	}
	R[low] = R[0];
	return low;
}// Partition

void MyQSort(ElemType R[], int s, int t) {
	// �Լ�¼����R[s..t]���п�������
	int pivotloc;
	if (s < t - 1) {							// ���ȴ���1
		pivotloc = Partition(R, s, t);			// �� R[s..t] ����һ�λ���
		MyQSort(R, s, pivotloc - 1);			// �Ե������еݹ�����pivotloc������λ��
		MyQSort(R, pivotloc + 1, t);			// �Ը������еݹ�����
	}
} // MyQSort

void QuickSort(SqList& L) {		// ��˳�����п�������
	MyQSort(L.r, 1, L.length);
	printf("����ɹ�������������Ϊ:\n");
	for (int i = 1; i < L.length; i++) {
		printf("%d%c ", L.r[i].key, L.r[i].record);
	}
} // QuickSort

int main() {
	BiTree T,p;
	ElemType e;
	p = NULL;
	printf("---------------------���������н������������---------------------\n");
	printf("�밴�����������������������У��ؼ�����ǰ��¼�ں��磺23A(��Ϊ�ս�㣬������0#):\n");
	CreateBiTree(T);
	printf("�ɹ����������������\n");
	printf("--------------------���������������ʽ���в���--------------------\n");
	printf("���Ⱥ��������Ԫ�صĹؼ��ֺͼ�¼ֵ:\n");
	scanf("%d", &e.key);
	getchar();
	scanf("%c", &e.record);
	InsertBST(T, e);
	printf("------------------------------����ASL-----------------------------\n");
	GetSL(T, p);
	Callength(T);
	printf("������ƽ����������Ϊ:%.2f\n", 1.0 * (1.0*Sumlen / number));
	printf("------------------------------��������----------------------------\n");
	SqList L;
	L.length = 0;
	printf("������������У������������������������,������0#ʱ�����������:\n");
	for (int i = 1;; i++) {
		RecordType record;			
		KeyType key;
		scanf("%d%c", &key, &record);
		if (key == 0 && record == '#')	break;
		L.r[i].key = key;
		L.r[i].record = record;
		L.length++;
	}
	QuickSort(L);

	return 0;
}
