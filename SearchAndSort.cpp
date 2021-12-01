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
typedef struct ElemType {		//待查/排数据的类型
	RecordType record;			//记录
	KeyType key;				//关键字
}ElemType;

typedef struct {				//顺序表类型
	ElemType r[MAXSIZE + 1];	//r[0]闲置
	int length;					//顺序表长度
}SqList;
/*
（1）编程实现一种查找算法（如折半查找、二叉排序树的查找、哈希查找等），并计算相应的ASL。
（2）编程实现一种内部排序算法（如插入排序、快速排序等）。
*/
//--------------------------------------二叉排序树的查找----------------------------------------
//二叉链表的存储结构
typedef struct BiTNode { // 结点结构
	ElemType data;
	int SL;
	struct BiTNode* lchild, * rchild;
	// 左右孩子指针
} BiTNode, * BiTree;

Status CreateBiTree(BiTree& T) {
	//以先序序列手动建立排序二叉树
	char ch;
	int key;
	//printf("请输入结点的关键字：\n");
	scanf("%d", &key);
	//getchar();
	//printf("请输入结点的记录：\n");
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data.record = ch; // 生成根结点 
		T->data.key = key;
		CreateBiTree(T->lchild); // 构造左子树 
		CreateBiTree(T->rchild); // 构造右子树 
	}
	return OK;
} // CreateBiTree

Status SearchBST(BiTree T, KeyType key,BiTree f, BiTree& p) {
	// 在根指针 T 所指二叉排序树中递归地查找其关键字等于key 的数据元素，若查找成功，
	// 则返回指针 p 指向该数据元素的结点，并返回函数值为TRUE;否则表明查找不成功，返回
	// 指针 p 指向查找路径上访问的最后一个结点，并返回函数值为FALSE, 指针 f 指向当前访问
	// 的结点的双亲，其初始调用值为NULL
	if (!T) {
		p = f;
		printf("查找失败！原二叉树中没有待查的元素！\n");
		return FALSE;
	} // 查找不成功
	else if (key == T->data.key){
		p = T; 
		if (f != NULL) {
			printf("查找成功！待查元素在原二叉树中！其父母结点的关键字为：%d, 记录为:%c\n", f->data.key, f->data.record);
		}
		else {
			printf("查找成功！待查元素在原二叉树中！且其 所在节点为根结点\n");
		}
		return TRUE; 
	} // 查找成功
	else if (key < T->data.key)
		SearchBST(T->lchild, key, T, p);	// 在左子树中继续查找
	else									
		SearchBST(T->rchild, key, T, p);	// 在右子树中继续查找
} //SearchBST

Status InsertBST(BiTree& T, ElemType e) {
	// 当二叉排序树中不存在关键字等于 e.key 的数据元素时，插入元素值为 e 的结点，并返回 TRUE; 
	// 否则，不进行插入并返回FALSE
	BiTree s,p;
	if (!SearchBST(T, e.key, NULL, p)) {
		s = (BiTree)malloc(sizeof(BiTNode));			// 为新结点分配空间
		s->data = e;
		s->lchild = s->rchild = NULL;
		if (!p) T = s;									// 插入 s 为新的根结点
		else if (e.key < p->data.key)
			p->lchild = s;								// 插入 *s 为 *p 的左孩子
		else 
			p->rchild = s;								// 插入 *s 为 *p 的右孩子
		printf("成功将结点插入原二叉树中！新结点的父母结点的关键字为：%d, 记录为:%c\n",p->data.key,p->data.record);
		return TRUE;									// 插入成功
	}
	else return FALSE;
} // Insert BST

Status GetSL(BiTree& T, BiTree& p) {
	//先序遍历二叉树并计算每个几点的搜索长度
	if (T) {
		if (p != NULL)	T->SL = p->SL + 1;
		else  T->SL = 1;
		GetSL(T->lchild, T);	//遍历左子树
		GetSL(T->rchild, T);	//遍历右子树
	}
	return OK;
}

Status Callength(BiTree& T) {
	//先序遍历二叉树，并计算树的结点个数和总搜索长度
	if (T) {
		number++;
		Sumlen += T->SL;
		Callength(T->lchild);	//遍历左子树
		Callength(T->rchild);	//遍历右子树
	}
	return OK;
}

//-----------------------------------------快速排序------------------------------------------
int Partition(ElemType R[], int low, int high) {
	R[0] = R[low]; 
	KeyType pivotkey;
	pivotkey = R[low].key; // 枢轴
	while (low < high) {
		while (low < high && R[high].key >= pivotkey)
			--high; // 从右向左搜索
		R[low] = R[high];
		while (low < high && R[low].key <= pivotkey)
			++low; // 从左向右搜索
		R[high] = R[low];
	}
	R[low] = R[0];
	return low;
}// Partition

void MyQSort(ElemType R[], int s, int t) {
	// 对记录序列R[s..t]进行快速排序
	int pivotloc;
	if (s < t - 1) {							// 长度大于1
		pivotloc = Partition(R, s, t);			// 对 R[s..t] 进行一次划分
		MyQSort(R, s, pivotloc - 1);			// 对低子序列递归排序，pivotloc是枢轴位置
		MyQSort(R, pivotloc + 1, t);			// 对高子序列递归排序
	}
} // MyQSort

void QuickSort(SqList& L) {		// 对顺序表进行快速排序
	MyQSort(L.r, 1, L.length);
	printf("排序成功！排序后的序列为:\n");
	for (int i = 1; i < L.length; i++) {
		printf("%d%c ", L.r[i].key, L.r[i].record);
	}
} // QuickSort

int main() {
	BiTree T,p;
	ElemType e;
	p = NULL;
	printf("---------------------以先序序列建立排序二叉树---------------------\n");
	printf("请按先序次序输入二叉树结点的序列，关键字在前记录在后，如：23A(若为空结点，则输入0#):\n");
	CreateBiTree(T);
	printf("成功建立排序二叉树！\n");
	printf("--------------------以排序二叉树的形式进行查找--------------------\n");
	printf("请先后输入待查元素的关键字和记录值:\n");
	scanf("%d", &e.key);
	getchar();
	scanf("%c", &e.record);
	InsertBST(T, e);
	printf("------------------------------计算ASL-----------------------------\n");
	GetSL(T, p);
	Callength(T);
	printf("该树的平均搜索长度为:%.2f\n", 1.0 * (1.0*Sumlen / number));
	printf("------------------------------快速排序----------------------------\n");
	SqList L;
	L.length = 0;
	printf("请输入待排序列，输入规则与上述二叉树相似,当输入0#时表明输入结束:\n");
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
