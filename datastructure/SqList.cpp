//线性表的顺序存储结构
//用数组存储顺序表
#define MAXSIZE 20
typedef int ElemType;
//定义顺序存储的结构
typedef struct
{
	ElemType data[MAXSIZE];
	int length;
}SqList;
//获取元素的操作
ElemType GetElem(SqList L, int i, ElemType* e)
{
	if (L.length == 0 || i<1 || i>L.length)
		return 0;
	*e = L.data[i - 1];
	return 1;
}
// 插入
int ListInsert(SqList &L, int i, ElemType e)
{
	int k;
	if (L.length == MAXSIZE)
		return 0;
	if (i<1 || i>L.length + 1)
		return 0;
	if (i <= L.length) {
		for (k = L.length - 1; k >= i - 1; k--)
			L.data[k + 1] = L.data[k];
	}
	L.data[i - 1] = e;
	L.length++;
	return 1;
}
//删除
int ListDelete(SqList& L, int i, ElemType *e)
{
	
	if (i<1 || i>L.length)
		return 0;
	*e = L.data[i - 1];
	if (i < L.length)
	{
		for (int k = i; k < L.length; k++) {
			L.data[k - 1] = L.data[k];
		}
	}
	L.length--;
	return 1;
}