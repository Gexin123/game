#include<iostream>
#define MAXSIZE 100
typedef int ElemType;
typedef struct
{
	ElemType data[MAXSIZE];
	int front;
	int rear;
}SqQueue;
bool InitQueue(SqQueue& Q)
{
	Q.front = 0;
	Q.rear = 0;
	return true;
}
int QueueLength(SqQueue& q)
{
	return (q.rear - q.front + MAXSIZE) % MAXSIZE;
}

//循环队列的入队操作
bool PushQueue(SqQueue& q, ElemType e)
{
	if ((q.rear + 1) % MAXSIZE == q.front)
		return false;
	q.data[q.rear] = e;
	q.rear = (q.rear + 1) % MAXSIZE;
	return true;
}
//出队
bool PopQueue(SqQueue& q, ElemType* e)
{
	if (q.rear == q.front)
		return false;
	*e = q.data[q.front];
	q.front = (q.front + 1) % MAXSIZE;
	return true;
}


//队列的链式存储结构
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
typedef struct
{
	QueuePtr front, rear;
}LinkQueue;

bool InsertQueue(LinkQueue& Q, ElemType e)
{
	QueuePtr q = (QueuePtr)malloc(sizeof(QNode));
	q->data = e;
	Q.rear->next = q;
	q->next = NULL;
	Q.rear = q;
	return true;
}
bool DeleteQueue(LinkQueue& Q, ElemType* e)
{
	if (Q.front == Q.rear)
		return false;
	QueuePtr p = Q.front->next;
	*e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	free(p);
	return true;

}