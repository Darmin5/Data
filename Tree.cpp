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
//��������Ĵ洢�ṹ
typedef struct BiTNode { // ���ṹ
	TElemType data;
	struct BiTNode* lchild, * rchild;
	// ���Һ���ָ��
} BiTNode, * BiTree;
//�������еĴ洢�ṹ
typedef struct QNode {
	BiTree data; // ָ�����������ָ��
	struct QNode* next;
} QNode, * QueuePtr;


typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


Status CreateBiTree(BiTree& T) {
	//���������н���������
	char ch;
	scanf("%c", &ch);
	if (ch == '#') T = NULL;
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
			exit(OVERFLOW);
		T->data = ch; // ���ɸ���� 
		CreateBiTree(T->lchild); // ���������� 
		CreateBiTree(T->rchild); // ���������� 
	}
	return OK;
} // CreateBiTree

void visit(TElemType& e) {
	printf("%c ", e);
}

Status PreOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//�������������
	if (T) {
		visit(T->data);		//���ʽ��
		PreOrder(T->lchild, visit);	//����������
		PreOrder(T->rchild, visit);	//����������
	}
	return OK;
}

Status InOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//�������������
	if (T) {
		InOrder(T->lchild, visit);	//����������
		visit(T->data);		//���ʽ��
		InOrder(T->rchild, visit);	//����������
	}
	return OK;
}

Status PostOrder(BiTree& T, void (*visit)(TElemType& e)) {
	//�������������
	if (T) {
		PostOrder(T->lchild, visit);	//����������
		PostOrder(T->rchild, visit);	//����������
		visit(T->data);		//���ʽ��
	}
	return OK;
}

void CountLeaf(BiTree T, int& count) {
	//ͳ�ƶ������е�Ҷ�ӽڵ�ĸ���
	if (T) {
		if ((!T->lchild) && (!T->rchild))	//�����û����������������������ý��ΪҶ�ӽ��
			count++; // ��Ҷ�ӽ����� 
		CountLeaf(T->lchild, count);	//������������Ҷ�ӽ��ĸ���
		CountLeaf(T->rchild, count);	//������������Ҷ�ӽ��ĸ���
	} // if
} // CountLeaf

int Depth(BiTree T) {
	// ���ض���������� (�ݹ��㷨)
	int depthval, depthLeft, depthRight;
	if (!T) depthval = 0;
	else {
		depthLeft = Depth(T->lchild);	//���������������
		depthRight = Depth(T->rchild);	//���������������
		depthval = 1 + (depthLeft > depthRight ? depthLeft : depthRight);
	}
	return depthval;
}
//���еĲ���
Status InitQueue(LinkQueue& Q) {
	//����һ���ն���Q
	Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q.front) exit(OVERFLOW);
	Q.front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue& Q) {
	//���ٶ���
	while (Q.front) {
		Q.rear = Q.front->next;
		free(Q.front);
		Q.front = Q.rear;
	}
	return OK;
}

Status EnQueue(LinkQueue& Q, BiTree e) {
	//����Ԫ��eΪQ���µĶ�βԪ��(���)
	QueuePtr p;
	p = (QueuePtr)malloc(sizeof(QNode));
	if (!p) exit(OVERFLOW);
	p->data = e;	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return OK;
}

BiTree DeQueue(LinkQueue& Q) {
	//�����в��գ���ɾ��Q�Ķ�ͷԪ�أ���e������ֵ��������OK�����ӣ�
	//���򷵻�ERROR
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
	//�ж϶����Ƿ�Ϊ�գ����򷵻�OK�����򷵻�ERROR
	if (Q.front == Q.rear) {
		return OK;
	}
	return ERROR;
}
Status LevelTraverse(BiTree T, void(*Visit) (TElemType& e)) {
	//���ж������Ĳ�α���
	// ��ʼ�����У����е�Ԫ��Ϊ�������Ľ��ָ��
	LinkQueue Q;
	BiTree p;
	InitQueue(Q);
	if (T != NULL) {
		// ���ʸ�
		Visit(T->data);
		// EnQueue( )Ϊ��Ӻ�����TΪ����ӵ�Ԫ��
		EnQueue(Q, T);
		// �Ӷ�����ȡ�ѱ����ʵġ��������Һ�����δ���ʵĽ��ָ��
		// �����亢��
		while (!EmptyQueue(Q)) { // �Ӳ�Ϊ��,������δ�����亢�ӵĽ��
		// DeQueue( )Ϊ���Ӻ���������ԭ��ͷԪ����Ϊ����ֵ����
			p = DeQueue(Q);
			// ��������
			if (p->lchild != NULL) {
				Visit(p->lchild->data);
				EnQueue(Q, p->lchild);
			}
			// �����Һ���
			if (p->rchild != NULL) {
				Visit(p->rchild->data);
				EnQueue(Q, p->rchild);
			}
		}
	}
	return OK;
}

//-----�շ������ͺշ�������Ĵ洢��ʾ-----
typedef struct {
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode, * HuffmanTree;

typedef char** HuffmanCode;

void Select(HuffmanTree& HT, int n, int& s1, int& s2) {
	//��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
	int i;
	s1 = 1;		//s1����Сֵ���±�
	s2 = 1;		//s2�Ǵ���Сֵ���±�
	unsigned int min;	//������Сֵ�ĳ�ֵ
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
	//w���n���ַ���Ȩֵ����>0��������շ�����HT�������n���ַ��ĺշ�������HC
	if (n <= 1) return;
	int m, c, i, start, s1, s2;
	unsigned int f;
	char* cd;
	HuffmanTree p;
	m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));			//0�ŵ�Ԫδ��
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
	for (i = n + 1; i <= m; ++i) {								//���շ�����,HT�ĵ�1����n��Ԫ�ؾ�Ϊ�ַ���Ҷ�ӽ�㣩����n+1����m��Ԫ�ؾ�Ϊ�����
		//��HT[1...i-1]ѡ��parentΪ0��weight��С��������㣬����ŷֱ�Ϊs1��s2
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//��Ҷ�ӵ���������ÿ���ַ��ĺշ�������
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));	//����n���ַ������ͷָ�����
	cd = (char*)malloc(n * sizeof(char));				//���������Ĺ����ռ�
	cd[n - 1] = '\0';									//���������
	for (i = 1; i <= n; ++i) {							//����ַ���շ�������
		start = n - 1;									//���������λ��
		for (c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent)	//��Ҷ�ӵ������������
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		HC[i] = (char*)malloc((n - start) * sizeof(char));	//Ϊ��i���ַ��������ռ�
		strcpy(HC[i], &cd[start]);							//��cd���Ʊ��루������HC
	}
	free(cd);
}

int main() {
	BiTree T;
	HuffmanTree HT;
	HuffmanCode HC;
	printf("����������������������ֵ:\n");
	CreateBiTree(T);
	printf("\n");
	printf("�����������������:");
	PreOrder(T, visit);
	printf("\n");
	printf("�����������������:");
	InOrder(T, visit);
	printf("\n");
	printf("�����������������:");
	PostOrder(T, visit);
	printf("\n");
	printf("�����������������:");
	LevelTraverse(T, visit);
	printf("\n");
	printf("����շ�����HT�������n(n<100)���ַ��ĺշ�������HC:\n");
	printf("�����ַ�����\n");
	char a[101];
	unsigned w[101];
	scanf("%s", a);
	int n = strlen(a);
	int i;
	printf("���ַ����е��ַ�����Ϊ��%d,��������Ӧ������Ȩֵ��", n);
	for (i = 0; i < n; i++)	scanf("%u", &w[i]);
	printf("�����շ���������շ�������:\n");
	HuffmanCoding(HT, HC, w, n);
	for (int i = 1; i <= n; i++) {
		printf("%c:%s\n", a[i - 1], HC[i]);
	}
	return OK;
}
