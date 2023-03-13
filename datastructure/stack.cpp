//栈的顺序存储结构
//栈的结构定义
#include <iostream>
#define MAXSIZE 100
typedef int ElemType;
typedef struct
{
	ElemType date[MAXSIZE];
	int top;
}SqStack;

//进栈操作push
bool push(SqStack& s, ElemType e)
{
	if (s.top == MAXSIZE - 1)
		return false;
	s.top++;
	s.date[s.top] = e;
	return true;
}
//出栈操作pop
bool pop(SqStack& s, ElemType* e)
{
	if (s.top == -1)
		return false;
	*e = s.date[s.top];
	s.top--;
	return true;
}

//栈的链式存储结构
typedef struct StackNode
{
	ElemType date;
	struct StackNode* next;
}StackNode,*LinkStackPtr;
typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;
//进栈
bool Push(LinkStack* S, ElemType e)
{
	LinkStackPtr s = (LinkStackPtr)malloc(sizeof(StackNode));
	s->date = e;
	s->next = S->top;
	S->top = s;
	S->count++;
	return true;
}
//出栈
bool Pop(LinkStack* S, ElemType* e)
{
	*e = S->top->date;
	LinkStackPtr p = S->top;
	S->top = S->top->next;
	free(p);
	S->count--;
	return true;
}
