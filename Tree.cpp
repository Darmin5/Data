#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAXQSIZE 100

typedef int Status;
typedef int TElemType;
//二叉链表的存储结构
typedef struct BiTNode { // 结点结构
	TElemType data;
	struct BiTNode* lchild, * rchild;
	// 左右孩子指针
} BiTNode, * BiTree;
//单链队列的存储结构
typedef struct QNode {
	BiTree data; // 指向二叉树结点的指针
	struct QNode* next;
} QNode, * QueuePtr;


typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


Status CreateBiTree(BiTree& T) {
	//以先序序列建立二叉树
	char ch;
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch; // 生成根结点 
		CreateBiTree(T->lchild); // 构造左子树 
		CreateBiTree(T->rchild); // 构造右子树 
	}
	return OK;
} // CreateBiTree

void visit(TElemType& e) {
	printf("%c ", e);
}

Status PreOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//先序遍历二叉树
	if (T) {
		visit(T->data);		//访问结点
		PreOrder(T->lchild, visit);	//遍历左子树
		PreOrder(T->rchild, visit);	//遍历右子树
	}
	return OK;
}

Status InOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//中序遍历二叉树
	if (T) {
		InOrder(T->lchild, visit);	//遍历左子树
		visit(T->data);		//访问结点
		InOrder(T->rchild, visit);	//遍历右子树
	}
	return OK;
}

Status PostOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//后序遍历二叉树
	if (T) {
		PostOrder(T->lchild, visit);	//遍历左子树
		PostOrder(T->rchild, visit);	//遍历右子树
		visit(T->data);		//访问结点
	}
	return OK;
}

void CountLeaf(BiTree T, int& count) {
	//统计二叉树中的叶子节点的个数
	if (T) {
		if ((!T->lchild) && (!T->rchild))	//若结点没有左子树或者右子树，则该结点为叶子结点
			count++; // 对叶子结点计数 
		CountLeaf(T->lchild, count);	//计算左子树中叶子结点的个数
		CountLeaf(T->rchild, count);	//计算右子树中叶子结点的个数
	} // if
} // CountLeaf

int Depth(BiTree T) {
	// 返回二叉树的深度 (递归算法)
	int depthval, depthLeft, depthRight;
	if (!T) depthval = 0;
	else {
		depthLeft = Depth(T->lchild);	//计算左子树的深度
		depthRight = Depth(T->rchild);	//计算右子树的深度
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}
//队列的操作
Status InitQueue(LinkQueue& Q) {
	//构造一个空队列Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue& Q) {
	//销毁队列
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue& Q, BiTree e) {
	//插入元素e为Q的新的队尾元素(入队)
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

BiTree DeQueue(LinkQueue& Q) {
	//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK（出队）
	//否则返回ERROR
	BiTree e;
	QueuePtr p;
	if (Q.front == Q.rear) return ERROR;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p) Q.rear = Q.front;
	free(p);
	return e;
}

Status EmptyQueue(LinkQueue& Q) {
	//判断队列是否为空，空则返回OK，否则返回ERROR
	if (Q.front == Q.rear) {
		return OK;
	}
	return ERROR;
}
Status LevelTraverse(BiTree T, void(*Visit) (TElemType& e)) {
	//进行二叉树的层次遍历
	// 初始化队列，队列的元素为二叉树的结点指针
	LinkQueue Q;
	BiTree p;
	InitQueue(Q);
	if (T != NULL) {
		// 访问根
		Visit(T->data);
		// EnQueue( )为入队函数，T为待入队的元素
		EnQueue(Q, T);
		// 从队列中取已被访问的、但其左右孩子尚未访问的结点指针
		// 访问其孩子
		while (!EmptyQueue(Q)) { // 队不为空,则尚有未访问其孩子的结点
		// DeQueue( )为出队函数，它将原队头元素作为返回值返回
			p = DeQueue(Q);
			// 访问左孩子
			if (p->lchild != NULL) {
				Visit(p->lchild->data);
				EnQueue(Q, p->lchild);
			}
			// 访问右孩子
			if (p->rchild != NULL) {
				Visit(p->rchild->data);
				EnQueue(Q, p->rchild);
			}
		}
	}
	return OK;
}

//-----赫夫曼树和赫夫曼编码的存储表示-----
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char** HuffmanCode;

void Select(HuffmanTree& HT, int n, int& s1, int& s2) {
	//在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
	int i;
	s1 = 1;		//s1是最小值的下标
	s2 = 1;		//s2是次最小值的下标
	unsigned int min;	//设置最小值的初值
	for (i = 1; i <= n; i++) {
		if (HT[i].parent == 0) {
			min = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= n; i++) {
		if (HT[i].parent == 0)
			if (HT[i].weight <= min) {
				min = HT[i].weight;
				s1 = i;
			}
	}//for
	HT[s1].parent = 1;
	for (i = 1; i <= n; i++) {
		if (HT[i].parent == 0) {
			min = HT[i].weight;
			break;
		}
	}
	for (i = 1; i <= n; i++) {
		if (HT[i].parent == 0)
			if (HT[i].weight <= min && i!=s1) {
				min = HT[i].weight;
				s2 = i;
			}
	}
}

void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, unsigned int* w, int n) {
	//w存放n个字符的权值（均>0），构造赫夫曼树HT，并求出n个字符的赫夫曼编码HC
	if (n <= 1) return;
	int m, c, i, start, s1, s2;
	unsigned int f;
	char* cd;
	HuffmanTree p;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0号单元未用
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w) {
		p->weight = *w;
		p->parent = 0;
		p->rchild = 0;
		p->lchild = 0;
	}
	for (; i <= m; ++i, ++p) {
		p->weight = 0;
		p->parent = 0;
		p->rchild = 0;
		p->lchild = 0;
	}
	for (i = n + 1; i <= m; ++i) {								//建赫夫曼树,HT的第1至第n个元素均为字符（叶子结点），第n+1至第m个元素均为根结点
		//在HT[1...i-1]选择parent为0且weight最小的两个结点，其序号分别为s1和s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//从叶子到根逆向求每个字符的赫夫曼编码
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));	//分配n个字符编码的头指针分量
	cd = (char*)malloc(n * sizeof(char));				//分配求编码的工作空间
	cd[n - 1] = '\0';									//编码结束符
	for (i = 1; i <= n; ++i) {							//逐个字符求赫夫曼编码
		start = n - 1;									//编码结束符位置
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//从叶子到根逆向求编码
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));	//为第i个字符编码分配空间
		strcpy(HC[i], &cd[start]);							//从cd复制编码（串）到HC
	}
	free(cd);
}

int main() {
	BiTree T;
	HuffmanTree HT;
	HuffmanCode HC;
	printf("按先序次序输入二叉树结点的值:\n");
	CreateBiTree(T);
	printf("\n");
	printf("先序遍历上述二叉树:");
	PreOrder(T, visit);
	printf("\n");
	printf("中序遍历上述二叉树:");
	InOrder(T, visit);
	printf("\n");
	printf("后序遍历上述二叉树:");
	PostOrder(T, visit);
	printf("\n");
	printf("层序遍历上述二叉树:");
	LevelTraverse(T, visit);
	printf("\n");
	printf("构造赫夫曼树HT，并求出n(n<100)个字符的赫夫曼编码HC:\n");
	printf("输入字符串：\n");
	char a[101];
	unsigned w[101];
	scanf("%s", a);
	int n = strlen(a);
	int i;
	printf("该字符串中的字符个数为：%d,请输入相应个数的权值：", n);
	for (i = 0; i < n; i++)	scanf("%u", &w[i]);
	printf("建立赫夫曼树，求赫夫曼编码:\n");
	HuffmanCoding(HT, HC, w, n);
	for (int i = 1; i <= n; i++) {
		printf("%c:%s\n", a[i - 1], HC[i]);
	}
	return OK;
}
