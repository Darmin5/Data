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
/*（1）建立无向图和有向图的邻接矩阵存储，计算顶点的度，并输出图的基本信息。
（2）建立有向图的邻接表存储表示，并根据存储计算顶点的出度和入度，然后输出图的基本信息。
（3）编写完整的程序实现AOV网的拓扑排序。
（4）编程求AOE网的关键路径。
（5）编程实现单源点最短路径的Dijkstra算法。
注：（3）（4）(5) 可以任选其一完成
*/
typedef int Status;
typedef int SElemType;
typedef int InfoType;
typedef int VRType;
typedef char VertexType;
typedef enum { DG, DN, UDG, UDN }GraphKind;


//----------------------------------------------图的邻接矩阵存储及其操作--------------------------------------------------
typedef struct ArcCell { // 弧的定义
	VRType adj; // VRType是顶点关系类型。对无权图，用1或0表示相邻否；对带权图，则为权值类型。
	//InfoType* info; // 该弧相关信息的指针
} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct { // 图的定义
	VertexType vexs[MAX_VERTEX_NUM];	// 顶点信息
	AdjMatrix arcs;					// 邻接矩阵
	int vexnum, arcnum;					// 顶点数，弧数
	GraphKind kind;						// 图的种类标志
} MGraph;

Status LocateVex(MGraph& G, char v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i])
			return i;
	}
}

Status CreateDG(MGraph& G) {
	//用邻接矩阵构造有向图
	int i, j, k;
	char v1, v2;
	printf("请分别输入有向图的顶点数、弧数:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//输入图的定点数、弧数
	printf("请分别输入各顶点的值:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();	//吞一下空格
		scanf("%c", &G.vexs[i]);		//构造顶点向量
	}
	for (i = 0; i < G.vexnum; i++)		//初始化邻接矩阵
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY };
	printf("请输入该图的弧:");
	for (k = 0; k < G.arcnum; k++) {	//构造邻接矩阵
		getchar();
		scanf("%c%c", &v1, &v2);		//输入一条边依附的顶点
		i = LocateVex(G, v1);	j = LocateVex(G, v2);
		G.arcs[i][j].adj = 1;
	}
	return OK;
}

Status CreateUDG(MGraph& G) {
	//构造无向图
	int i, j, k;
	char v1, v2;
	printf("请分别输入有向图的顶点数、弧数:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//输入图的定点数、弧数
	printf("请分别输入各顶点的值:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();	//吞一下空格
		scanf("%c", &G.vexs[i]);		//构造顶点向量
	}
	for (i = 0; i < G.vexnum; i++)		//初始化邻接矩阵
		for (j = 0; j < G.vexnum; j++)
			G.arcs[i][j] = { INFINITY };
	printf("请输入该图的弧:");
	for (k = 0; k < G.arcnum; k++) {	//构造邻接矩阵
		getchar();
		scanf("%c%c", &v1, &v2);		//输入一条边依附的顶点
		i = LocateVex(G, v1);	j = LocateVex(G, v2);		//确定v1和v2在G中的位置
		G.arcs[i][j].adj = 1;
		G.arcs[j][i] = G.arcs[i][j];		//设置对称弧
	}
	return OK;
}
Status GetDGDegree(MGraph& G, char v) {
	//计算有向图中顶点v的度
	int i, j;
	int Outdegree, Indegree;
	Outdegree = 0;
	Indegree = 0;
	i = LocateVex(G, v);
	for (j = 0; j < G.vexnum; j++) {		//计算出度
		if (G.arcs[i][j].adj == 1)
			Outdegree++;
	}
	printf("有向图中顶点%c的出度的数目是%d\n", v, Outdegree);
	for (j = 0; j < G.vexnum; j++) {		//计算入度
		if (G.arcs[j][i].adj == 1)
			Indegree++;
	}
	printf("有向图中顶点%c的入度的数目是%d\n", v, Indegree);
	return OK;
}

Status GetUDGDegree(MGraph& G, char v) {
	//计算无向图中顶点v的度
	int i, j;
	int Degree;
	Degree = 0;
	i = LocateVex(G, v);
	for (j = 0; j < G.vexnum; j++) {		//计算度
		if (G.arcs[i][j].adj == 1)
			Degree++;
	}
	printf("无向图中顶点%c的度的数目是%d\n", v, Degree);
	return OK;
}

Status ShowG(MGraph& G) {
	//输出图的相关信息
	switch (G.kind) {
	case DG:printf("该图为有向图\n"); break;
	case UDG:printf("该图为无向图\n"); break;
	}
	printf("该图拥有顶点数：%d	弧数：%d\n", G.vexnum, G.arcnum);
	printf("该图的顶点分别为：\n");
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
	//采用数组（邻接矩阵）表示法，构造图G
	scanf("%d", &G.kind);
	switch (G.kind) {
	case DG:return CreateDG(G);//构造有向图G
	case UDG:return CreateUDG(G);//构造无向图
	}
}
//---------------------------------------------------有向图的邻接表存储及其应用-----------------------------------------------------
typedef struct ArcNode {			//顶点链表的结构
	int adjvex;						// 该弧所指向的顶点的位置
	struct ArcNode* nextarc;		// 指向下一条弧的指针
	//InfoType* info;					// 该弧相关信息的指针
} ArcNode;

typedef struct VNode {				//邻接表的结点结构
	VertexType data;				// 顶点信息
	ArcNode* firstarc;				// 指向第一条依附该顶点的弧
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {					//有向图的邻接表存储结构
	AdjList vertices;				//邻接表
	int vexnum, arcnum;				//图的当前顶点数和弧数
	GraphKind kind;						// 图的种类标志(邻接表可用于有向图或者无向图)
} ALGraph;

Status LocateALGVex(ALGraph& G, char v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (v == G.vertices[i].data)
			return i;
	}
}

Status CreateALG(ALGraph& G) {
	//以邻接表结构创造有向图
	//步骤：先输入图的顶点数和弧数，然后输入顶点向量，最后将顶点相连
	printf("请分别输入有向图的顶点数、弧数:");
	scanf("%d%d", &G.vexnum, &G.arcnum);	//输入图的定点数、弧数
	int i, j, k;
	printf("请分别输入各顶点的值:");
	for (i = 0; i < G.vexnum; i++) {
		getchar();
		scanf("%c", &G.vertices[i].data);	//输入顶点向量
		G.vertices[i].firstarc = NULL;
	}
	char v1, v2;
	printf("请输入该图的弧:");
	for (k = 0; k < G.arcnum; k++) {	//连接顶点
		getchar();
		scanf("%c%c", &v1, &v2);		//输入一条边依附的顶点
		i = LocateALGVex(G, v1);	j = LocateALGVex(G, v2);
		ArcNode* p, * q;
		q = (ArcNode*)malloc(sizeof(ArcNode));
		q->adjvex = j;
		q->nextarc = NULL;
		p = G.vertices[i].firstarc;
		if (p != NULL) {
			while (p->nextarc)	p = p->nextarc;
			p->nextarc = q;					//将结点连接到链表上
		}
		else
			G.vertices[i].firstarc = q;
	}
	return OK;
}

Status GetALGDegree(ALGraph& G, char v) {
	//计算邻接表有向图中顶点v的度
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
	printf("邻接表有向图中顶点%c的出度的数目是%d\n", v, Outdegree);
	for (j = 0; j < G.vexnum; j++) {
		p = G.vertices[j].firstarc;
		while (p) {
			if (p->adjvex == i)
				Indegree++;
			p = p->nextarc;
		}//while
	}//for
	printf("邻接表有向图中顶点%c的入度的数目是%d\n", v, Indegree);
	return OK;
}

Status ShowALG(ALGraph& G) {
	//输出图的相关信息
	switch (G.kind) {
	case DG:printf("该图为有向图\n"); break;
	case UDG:printf("该图为无向图\n"); break;
	}
	printf("该图拥有顶点数：%d	弧数：%d\n", G.vexnum, G.arcnum);
	printf("该图的顶点分别为：\n");
	for (int i = 0; i < G.vexnum; i++) {
		printf("%c \n", G.vertices[i].data);
		GetALGDegree(G, G.vertices[i].data);
	}
	printf("\n");
	return OK;
}

//----------------------------------------------------------实现AOV网的拓扑排序----------------------------------------------------------------
Status* FindInDegree(ALGraph& G, int* indegree) {
	//对各顶点求入度indegree[0..vexnum-1] 
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

typedef struct {		//顺序栈的存储结构
	SElemType* base;
	SElemType* top;
	int stacksize;
}SqStack;
//以下为顺序栈的基本操作
Status InitStack(SqStack& S) {
	//构造一个空栈
	S.base = (SElemType*)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!S.base)	exit(OVERFLOW);
	S.top = S.base;
	S.stacksize = STACK_INIT_SIZE;
	return OK;
}

Status Push(SqStack& S, SElemType e) {
	//插入e为新的栈顶元素
	if (S.top - S.base >= S.stacksize) {	//栈满，增加存储空间
		S.base = (SElemType*)realloc(S.base, (S.stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!S.base)	exit(OVERFLOW);
		S.top = S.base + S.stacksize;
		S.stacksize += STACKINCREMENT;
	}
	*S.top++ = e;
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base) {
		return ERROR;
	}
	e = *--S.top;
	return OK;
}

Status StackEmpty(SqStack S) {
	//判断栈空
	if (S.top == S.base) {
		return OK;
	}
	return ERROR;
}

Status TopologicalSort(ALGraph G) {
	//有向图G采用邻接表存储结构
	//若G无回路，则输出G的顶点的一个拓扑序列并返回OK，否则ERROR
	int i, count, k;
	int* indegree;
	indegree = FindInDegree(G, indegree);		//对各顶点求入度indegree[0..vexnum-1] 
	SqStack S;
	ArcNode* p;
	InitStack(S);
	for (i = 0; i < G.vexnum; i++)				//建零入度顶点栈 
		if (!indegree[i])
			Push(S, i);							//入度为零者进栈 
	count = 0;									//对输出顶点计数 
	printf("该图的拓朴序列为：\n");
	while (!StackEmpty(S)) {
		Pop(S, i);
		printf("%d:%c ", i, G.vertices[i].data);
		count++;								//输出i号顶点并计数 
		for (p = G.vertices[i].firstarc; p; p = p->nextarc) {
			k = p->adjvex;						//对i号顶点的每个邻接点的入度减1 
			if (!(--indegree[k]))				//若入度为零，则入栈 
				Push(S, k);
		}
	}
	printf("\n"); 
	if (count < G.vexnum) {			//该有向图有回路 
		printf("该图有回路，不是一个合法的AOV网！\n");
		return ERROR;			
	}
	else {
		printf("该图中没有环，是一个合法的AOV网~ ^_^\n");
		return OK;
	}
}

int main() {
	MGraph G1, G2;
	ALGraph G3;
	G3.kind = DG;
	G1.kind = DG;
	G2.kind = UDG;
	printf("--------------建立邻接矩阵无向图--------------\n");
	CreateUDG(G2);
	printf("--------------展示邻接矩阵无向图--------------\n");
	ShowG(G2);
	printf("--------------建立邻接矩阵有向图--------------\n");
	CreateDG(G1);
	printf("--------------展示邻接矩阵无向图--------------\n");
	ShowG(G1);
	printf("---------------建立邻接表有向图---------------\n");
	CreateALG(G3);
	printf("---------------展示邻接表有向图---------------\n");
	ShowALG(G3);
	printf("--------------实现AOV网的拓朴排序-------------\n");
	printf("1.先建立一个AOV网\n");
	ALGraph G4;
	G4.kind = DG;
	CreateALG(G4);
	printf("2.对该AOV网进行拓朴排序\n");
	TopologicalSort(G4);
	return 0;
}
