//线性表的链式存储结构
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#define MAXSIZE 1000
using namespace std;

typedef int ElemType;
typedef struct Node
{
	ElemType data;
	struct Node* next;
}*LinkList,LNode;


//单链表的的读取
bool GetElem(ElemType& e, int i, LinkList L)
{
	while (L != NULL && i > 0)
	{
		i--;
		L = L->next;
	}
	if (i = 0 && L != NULL)
	{
		e = L->data;
		return true;
	}
	else {
		return false;
	}
}

//插入
bool InsertElem(int i, ElemType e, LinkList& L)
{
	int j = 1;
	while (L && j < i) {
		L = L->next;
		++j;
	}
	if (!L || j > i) {
		return false;
	}
	LinkList temp = (LinkList)malloc(sizeof(LNode));
	temp->data = e;
	temp->next = L->next;
	L->next = temp;
	return true;
}

//删除
bool ListDelete(LinkList& L, int i, ElemType* e)
{
	int j = 1;
	while (L->next && j < i) {
		L = L->next;
		++j;
	}
	if (!L || j > i) {
		return false;
	}
	L->next = L->next->next;
	*e = L->next->data;
	free(L->next);
	return true;
}

//单链表的创建：尾插法
void CreatList(LinkList& L, int n)
{
	L = (LinkList)malloc(sizeof(LNode));  //初始化;
	L->next = NULL;
	L->data = 0;
	srand(time(0));
	LinkList tail = L;
	for (int i = 0; i < n; i++)
	{
		LinkList temp = (LinkList)malloc(sizeof(LNode));
		temp->data = rand() % 100 + 1;
		tail->next = temp;
		tail = temp;
		temp = NULL;
		L->data++;
	}
	tail->next = NULL;
}
//单链表的删除
bool ClearList(LinkList& L)
{
	LinkList p, q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return true;
}


//静态链表:cur存储的是后继节点在数组中的下标

typedef struct
{
	ElemType data;
	int cur;
}StaticLinkList[MAXSIZE];

//节点的申请
int Malloc_SSL (StaticLinkList space)
{
	int i = space[0].cur;

	if (space[0].cur)
		space[0].cur = space[i].cur;

	return i;
}

//静态链表的长度计算
int ListLength(StaticLinkList L)
{
	int j = 0;
	int i = L[MAXSIZE - 1].cur;
	while (i)
	{
		i = L[i].cur;
		j++;
	}
	return j;
}

//插入操作
bool ListInsert(StaticLinkList L, int i, ElemType e)
{
	int k = MAXSIZE - 1;
	if (i<1 || i>ListLength(L) + 1)
		return false;
	int j = Malloc_SSL(L);
	if (j)
	{
		L[j].data = e;
		for (int l = 1; l < i; l++)
		     k = L[k].cur;
		L[j].cur = L[k].cur;
		L[k].cur = j;
		return true;
	}
}
//自定义free
void Free_SSL(StaticLinkList space, int k)
{
	space[k].cur = space[0].cur;
	space[0].cur = k;
}

//静态链表的删除操作
bool StaticListDelete(StaticLinkList L, int i)
{
	int j, k;
	if (i<1 || i>ListLength(L))
		return false;
	k = MAXSIZE - 1;
	for (j = 1; j < i; j++)
		k = L[k].cur;
	j = L[k].cur;
	L[k].cur = L[j].cur;
	Free_SSL(L, j);
	return true;
}


