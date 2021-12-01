#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10
typedef int Status;
typedef char SElemType;
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
//	printf("顺序栈初始化成功！\n");
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
//	printf("入栈成功！\n");
	return OK;
}

Status Pop(SqStack& S, SElemType& e) {
	//若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK，否则返回ERROR
	if (S.top == S.base) {
//	printf("当前栈为空！\n");
		return ERROR;
	}
	e = *--S.top;
//	printf("弹栈成功！弹出元素为：%d\n",e);
	return OK;
}

Status StackEmpty(SqStack S) {
	//判断栈空
	if (S.top == S.base) {
//		printf("当前栈为空！\n");
		return OK;
	}
//	printf("当前栈不为空！\n");
	return ERROR;
}
Status Matching(char* exp) {
	int state = 1;
	int i = 0;
	SqStack S;
	SElemType e;
	InitStack(S);
	while (i < strlen(exp) && state) {
		switch (exp[i]) {
		case '(': {Push(S, exp[i]); i++; break;}
		case ')': {
			SElemType c = *(S.top-1);			//这里要注意的是top指针并不是指向栈顶元素，而是指向栈顶元素的上面一个 
			if ((!StackEmpty(S)) && (c == '(')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case ')'
		case '{': {Push(S, exp[i]); i++; break; }
		case '}': {
			SElemType c = *(S.top-1);
			if ((!StackEmpty(S)) && (c == '{')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case '}'
		case '[': {Push(S, exp[i]); i++; break; }
		case ']': {
			SElemType c = *(S.top-1); 
			if ((!StackEmpty(S)) && (c == '[')) {
				Pop(S, e);
				i++;
			}//if
			else state = 0;
			break;
		}//case ']'
		}//switch
	}//while
	if (StackEmpty(S) && state) {
		printf("括号匹配成功！\n");
		return OK;
	}
	else {
		printf("括号匹配失败！\n");
		return ERROR;
	}
}
int main() {
	char bracket[100];
	scanf("%s", bracket);
	int len = strlen(bracket);
	Matching(bracket);
	return 0;
}
