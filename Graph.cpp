#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1 
#define OVERFLOW -2
#define INFINITY INT_MAX
#define MAX_VERTEX_NUM 20
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
/*��1����������ͼ������ͼ���ڽӾ���洢�����㶥��Ķȣ������ͼ�Ļ�����Ϣ��
��2����������ͼ���ڽӱ�洢��ʾ�������ݴ洢���㶥��ĳ��Ⱥ���ȣ�Ȼ�����ͼ�Ļ�����Ϣ��
��3����д�����ĳ���ʵ��AOV������������
��4�������AOE���Ĺؼ�·����
��5�����ʵ�ֵ�Դ�����·����Dijkstra�㷨��
ע����3����4��(5) ������ѡ��һ���
*/
typedef int Status;
typedef int SElemType;
typedef int InfoType;
typedef int VRType;
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN }GraphKind;


//----------------------------------------------ͼ���ڽӾ���洢�������--------------------------------------------------
typedef struct ArcCell { // ���Ķ���
	VRType adj; // VRType�Ƕ����ϵ���͡�����Ȩͼ����1��0��ʾ���ڷ񣻶Դ�Ȩͼ����ΪȨֵ���͡�
	//InfoType* info; // �û������Ϣ��ָ��
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct { // ͼ�Ķ���
	VertexType vexs[MAX_VERTEX_NUM];	// ������Ϣ
	AdjMatrix arcs;					// �ڽӾ���
	int vexnum, arcnum;					// ������������
	GraphKind kind;						// ͼ�������־
} MGraph;

Status LocateVex(MGraph& G, char v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i])
			return i;
	}
}

Status CreateDG(MGraph& G) {
	//���ڽӾ���������ͼ
	int i, j, k;
	char v1, v2;
	printf("��ֱ���������ͼ�Ķ�����������:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//����ͼ�Ķ�����������
	printf("��ֱ�����������ֵ:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();	//��һ�¿ո�
		scanf("%c", &G.vexs[i]);		//���춥������
	}
	for (i = 0; i < G.vexnum; i++)		//��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY };
	printf("�������ͼ�Ļ�:");
	for (k = 0; k < G.arcnum; k++) {	//�����ڽӾ���
		getchar();
		scanf("%c%c", &v1, &v2);		//����һ���������Ķ���
		i = LocateVex(G, v1);	j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
	}
	return OK;
}

Status CreateUDG(MGraph& G) {
	//��������ͼ
	int i, j, k;
	char v1, v2;
	printf("��ֱ���������ͼ�Ķ�����������:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//����ͼ�Ķ�����������
	printf("��ֱ�����������ֵ:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();	//��һ�¿ո�
		scanf("%c", &G.vexs[i]);		//���춥������
	}
	for (i = 0; i < G.vexnum; i++)		//��ʼ���ڽӾ���
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY };
	printf("�������ͼ�Ļ�:");
	for (k = 0; k < G.arcnum; k++) {	//�����ڽӾ���
		getchar();
		scanf("%c%c", &v1, &v2);		//����һ���������Ķ���
		i = LocateVex(G, v1);	j = LocateVex(G, v2);		//ȷ��v1��v2��G�е�λ��
		G.arcs[i][j].adj = 1;
		G.arcs[j][i] = G.arcs[i][j];		//���öԳƻ�
	}
	return OK;
}
Status GetDGDegree(MGraph& G, char v) {
	//��������ͼ�ж���v�Ķ�
	int i, j;
	int Outdegree, Indegree;
	Outdegree = 0;
	Indegree = 0;
	i = LocateVex(G, v);
	for (j = 0; j < G.vexnum; j++) {		//�������
		if (G.arcs[i][j].adj == 1)
			Outdegree++;
	}
	printf("����ͼ�ж���%c�ĳ��ȵ���Ŀ��%d\n", v, Outdegree);
	for (j = 0; j < G.vexnum; j++) {		//�������
		if (G.arcs[j][i].adj == 1)
			Indegree++;
	}
	printf("����ͼ�ж���%c����ȵ���Ŀ��%d\n", v, Indegree);
	return OK;
}

Status GetUDGDegree(MGraph& G, char v) {
	//��������ͼ�ж���v�Ķ�
	int i, j;
	int Degree;
	Degree = 0;
	i = LocateVex(G, v);
	for (j = 0; j < G.vexnum; j++) {		//�����
		if (G.arcs[i][j].adj == 1)
			Degree++;
	}
	printf("����ͼ�ж���%c�Ķȵ���Ŀ��%d\n", v, Degree);
	return OK;
}

Status ShowG(MGraph& G) {
	//���ͼ�������Ϣ
	switch (G.kind) {
	case DG:printf("��ͼΪ����ͼ\n"); break;
	case UDG:printf("��ͼΪ����ͼ\n"); break;
	}
	printf("��ͼӵ�ж�������%d	������%d\n", G.vexnum, G.arcnum);
	printf("��ͼ�Ķ���ֱ�Ϊ��\n");
	for (int i = 0; i < G.vexnum; i++) {
		printf("%c \n", G.vexs[i]);
		switch (G.kind) {
		case DG:GetDGDegree(G, G.vexs[i]); break;
		case UDG:GetUDGDegree(G, G.vexs[i]); break;
		}
	}
	printf("\n");
	return OK;
}

Status CreateGraph(MGraph& G) {
	//�������飨�ڽӾ��󣩱�ʾ��������ͼG
	scanf("%d", &G.kind);
	switch (G.kind) {
	case DG:return CreateDG(G);//��������ͼG
	case UDG:return CreateUDG(G);//��������ͼ
	}
}
//---------------------------------------------------����ͼ���ڽӱ�洢����Ӧ��-----------------------------------------------------
typedef struct ArcNode {			//��������Ľṹ
	int adjvex;						// �û���ָ��Ķ����λ��
	struct ArcNode* nextarc;		// ָ����һ������ָ��
	//InfoType* info;					// �û������Ϣ��ָ��
} ArcNode;

typedef struct VNode {				//�ڽӱ�Ľ��ṹ
	VertexType data;				// ������Ϣ
	ArcNode* firstarc;				// ָ���һ�������ö���Ļ�
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {					//����ͼ���ڽӱ�洢�ṹ
	AdjList vertices;				//�ڽӱ�
	int vexnum, arcnum;				//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;						// ͼ�������־(�ڽӱ����������ͼ��������ͼ)
} ALGraph;

Status LocateALGVex(ALGraph& G, char v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (v == G.vertices[i].data)
			return i;
	}
}

Status CreateALG(ALGraph& G) {
	//���ڽӱ�ṹ��������ͼ
	//���裺������ͼ�Ķ������ͻ�����Ȼ�����붥����������󽫶�������
	printf("��ֱ���������ͼ�Ķ�����������:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//����ͼ�Ķ�����������
	int i, j, k;
	printf("��ֱ�����������ֵ:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();
		scanf("%c", &G.vertices[i].data);	//���붥������
		G.vertices[i].firstarc = NULL;
	}
	char v1, v2;
	printf("�������ͼ�Ļ�:");
	for (k = 0; k < G.arcnum; k++) {	//���Ӷ���
		getchar();
		scanf("%c%c", &v1, &v2);		//����һ���������Ķ���
		i = LocateALGVex(G, v1);	j = LocateALGVex(G, v2);
		ArcNode* p, * q;
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = j;
		q->nextarc = NULL;
		p = G.vertices[i].firstarc;
		if (p != NULL) {
			while (p->nextarc)	p = p->nextarc;
			p->nextarc = q;					//��������ӵ�������
		}
		else
			G.vertices[i].firstarc = q;
	}
	return OK;
}

Status GetALGDegree(ALGraph& G, char v) {
	//�����ڽӱ�����ͼ�ж���v�Ķ�
	int i, j;
	int Outdegree, Indegree;
	Outdegree = 0, Indegree = 0;
	i = LocateALGVex(G, v);
	ArcNode* p;
	p = G.vertices[i].firstarc;
	while (p) {
		Outdegree++;
		p = p->nextarc;
	}//while
	printf("�ڽӱ�����ͼ�ж���%c�ĳ��ȵ���Ŀ��%d\n", v, Outdegree);
	for (j = 0; j < G.vexnum; j++) {
		p = G.vertices[j].firstarc;
		while (p) {
			if (p->adjvex == i)
				Indegree++;
			p = p->nextarc;
		}//while
	}//for
	printf("�ڽӱ�����ͼ�ж���%c����ȵ���Ŀ��%d\n", v, Indegree);
	return OK;
}

Status ShowALG(ALGraph& G) {
	//���ͼ�������Ϣ
	switch (G.kind) {
	case DG:printf("��ͼΪ����ͼ\n"); break;
	case UDG:printf("��ͼΪ����ͼ\n"); break;
	}
	printf("��ͼӵ�ж�������%d	������%d\n", G.vexnum, G.arcnum);
	printf("��ͼ�Ķ���ֱ�Ϊ��\n");
	for (int i = 0; i < G.vexnum; i++) {
		printf("%c \n", G.vertices[i].data);
		GetALGDegree(G, G.vertices[i].data);
	}
	printf("\n");
	return OK;
}

//----------------------------------------------------------ʵ��AOV������������----------------------------------------------------------------
Status* FindInDegree(ALGraph& G, int* indegree) {
	//�Ը����������indegree[0..vexnum-1] 
	int i, j, Indegree;
	indegree = (int*)malloc(G.vexnum * sizeof(int));
	ArcNode* p;
	for (i = 0; i < G.vexnum; i++) {
		Indegree = 0;
		for (j = 0; j < G.vexnum; j++) {
			p = G.vertices[j].firstarc;
			while (p) {
				if (p->adjvex == i)
					Indegree++;
				p = p->nextarc;
			}//while
		}//for
		indegree[i] = Indegree;
	}//for
	return indegree;
}

typedef struct {		//˳��ջ�Ĵ洢�ṹ
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;
//����Ϊ˳��ջ�Ļ�������
Status InitStack(SqStack& S) {
	//����һ����ջ
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)	exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack& S, SElemType e) {
	//����eΪ�µ�ջ��Ԫ��
	if (S.top - S.base >= S.stacksize) {	//ջ�������Ӵ洢�ռ�
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)	exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������OK�����򷵻�ERROR
	if (S.top == S.base) {
		return ERROR;
	}
	e = *--S.top;
	return OK;
}

Status StackEmpty(SqStack S) {
	//�ж�ջ��
	if (S.top == S.base) {
		return OK;
	}
	return ERROR;
}

Status TopologicalSort(ALGraph G) {
	//����ͼG�����ڽӱ�洢�ṹ
	//��G�޻�·�������G�Ķ����һ���������в�����OK������ERROR
	int i, count, k;
	int* indegree;
	indegree = FindInDegree(G, indegree);		//�Ը����������indegree[0..vexnum-1] 
	SqStack S;
	ArcNode* p;
	InitStack(S);
	for (i = 0; i < G.vexnum; i++)				//������ȶ���ջ 
		if (!indegree[i])
			Push(S, i);							//���Ϊ���߽�ջ 
	count = 0;									//������������ 
	printf("��ͼ����������Ϊ��\n");
	while (!StackEmpty(S)) {
		Pop(S, i);
		printf("%d:%c ", i, G.vertices[i].data);
		count++;								//���i�Ŷ��㲢���� 
		for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
			k = p->adjvex;						//��i�Ŷ����ÿ���ڽӵ����ȼ�1 
			if (!(--indegree[k]))				//�����Ϊ�㣬����ջ 
				Push(S, k);
		}
	}
	printf("\n"); 
	if (count < G.vexnum) {			//������ͼ�л�· 
		printf("��ͼ�л�·������һ���Ϸ���AOV����\n");
		return ERROR;			
	}
	else {
		printf("��ͼ��û�л�����һ���Ϸ���AOV��~ ^_^\n");
		return OK;
	}
}

int main() {
	MGraph G1, G2;
	ALGraph G3;
	G3.kind = DG;
	G1.kind = DG;
	G2.kind = UDG;
	printf("--------------�����ڽӾ�������ͼ--------------\n");
	CreateUDG(G2);
	printf("--------------չʾ�ڽӾ�������ͼ--------------\n");
	ShowG(G2);
	printf("--------------�����ڽӾ�������ͼ--------------\n");
	CreateDG(G1);
	printf("--------------չʾ�ڽӾ�������ͼ--------------\n");
	ShowG(G1);
	printf("---------------�����ڽӱ�����ͼ---------------\n");
	CreateALG(G3);
	printf("---------------չʾ�ڽӱ�����ͼ---------------\n");
	ShowALG(G3);
	printf("--------------ʵ��AOV������������-------------\n");
	printf("1.�Ƚ���һ��AOV��\n");
	ALGraph G4;
	G4.kind = DG;
	CreateALG(G4);
	printf("2.�Ը�AOV��������������\n");
	TopologicalSort(G4);
	return 0;
}
