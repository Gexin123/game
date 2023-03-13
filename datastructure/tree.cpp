//数的双亲表示法结点结构定义
#define MAX_TREE_SIZE 100
typedef int ElemType;
typedef struct PtNode
{
	ElemType data;
	int parent;
}PtNode;
typedef struct
{
	PtNode nodes[MAX_TREE_SIZE];
	int r, n;//根的位置和结点数
}PTree;

//孩子表示法
//孩子结点
typedef struct CTNode
{
	int child;
	struct CTNode* next;
}ChilePtr;
//表头结构
typedef struct
{
	ElemType data;
	ChilePtr firstchild;
}CTbox;
//树结构
typedef struct
{
	CTbox nodes[MAX_TREE_SIZE];
	int r, n;//根的位置和结点数
}CTree;