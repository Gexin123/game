#include <queue>
#include <iostream>
#include <stack>
using namespace std;

template <typename T>
struct BinTreeNode
{
	T data;
	BinTreeNode<T>* leftChild, * rightChild;
	BinTreeNode() : leftChild(NULL), rightChild(NULL) {}                                                           //无参构造函数
	BinTreeNode(T x, BinTreeNode<T>* l = NULL, BinTreeNode<T>* r = NULL) : data(x), leftChild(l), rightChild(r) {} //有参构造函数
};

//二叉树的类声明
template <typename T>
class BinaryTree
{
public:
    //构造函数
    BinaryTree() : root(NULL) {}
    //指定结束标志的构造函数
    BinaryTree(T value) : root(NULL), RefValue(value) {}
    //析构函数
    ~BinaryTree();
    //拷贝构造函数，拷贝二叉树(前序遍历的应用)
    BinaryTree(BinaryTree<T>& s);
    //使用广义表创建二叉树，以'#'字符代表结束
    void CreateBinTree();
    //前序遍历创建二叉树(前序遍历的应用)，用#表示空结点
    void CreateBinTree_PreOrder(BinTreeNode<T>*& subTree);
    //使用先序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Pre_In(const char* pre, const char* in);
    //使用后序遍历和中序遍历创建二叉树
    void CreateBinTreeBy_Post_In(const char* post, const char* in);

    //先序遍历（递归）
    void PreOrder(BinTreeNode<T>*& subTree);
    //中序遍历(递归)
    void InOrder(BinTreeNode<T>*& subTree);
    //后序遍历（递归）
    void PostOrder(BinTreeNode<T>*& subTree);
    //先序遍历(非递归1)
    void PreOrder_NoRecurve1(BinTreeNode<T>* p);
    //先序遍历(非递归2)
    void PreOrder_NoRecurve2();
    //中序遍历(非递归)
    void InOrder_NoRecurve();
    //后序遍历(非递归)
    void PostOrder_NoRecurve();
    //层次遍历(非递归)
    void LevelOrder(BinTreeNode<T> *p);

    //获取二叉树的根节点
    BinTreeNode<T>* getRoot();
    //获取current结点的父节点
    BinTreeNode<T>* Parent(BinTreeNode<T>* current);
    //获取current结点的左结点
    BinTreeNode<T>* LeftChild(BinTreeNode<T>* current);
    //获取current结点的右结点
    BinTreeNode<T>* RightChild(BinTreeNode<T>* current);

    //销毁函数
    void Destroy();
    //判断两颗二叉树是否相等(前序遍历的应用)
    bool operator==(BinaryTree<T>& s);
    //计算二叉树的结点的个数(后序遍历的应用)
    int Size();
    //计算二叉树的高度（后序遍历的应用）
    int Height();
    //判断二叉树是否为空
    bool Empty();
    //以广义表的形式输出二叉树(前序遍历的应用)
    void PrintBinTree();
    //翻转二叉树
    void InvertTree();

private:
    BinTreeNode<T>* root; //根节点
    T RefValue;           //数据输入停止的标志，需要一个构造函数
};

/*
前序遍历建立二叉树
每读入一个值，就为它建立结点。该结点作为根结点，
其地址通过函数的引用型参数 subTree 直接链接到作为实际参数的指针中。
然后，分别对根的左、右子树递归地建立子树，直到读入结束符号
*/
template<typename T>
void BinaryTree<T>::CreateBinTree_PreOrder(BinTreeNode<T> *&subTree)
{
    T item;
    if (cin >> item) {
        if (item != RefValue) {
            subTree = new BinTreeNode<T>(item);
            CreateBinTree_PreOrder(subTree->leftChild);  //递归创建左子树
            CreateBinTree_PreOrder(subTree->rightChild); //递归创建右子树
        }
        else {
            subTree = NULL;
        }
    }
}


//二叉树的先序遍历顺序为：根结点 -> 左孩子结点 -> 右孩子结点
template<typename T>
void BinaryTree<T>::PreOrder(BinTreeNode<T>*& subTree)
{
    if (subTree != NULL)
    {
        cout << subTree->data << " ";
        PreOrder(subTree->leftChild);
        PreOrder(subTree->rightChild);
    }
}


//二叉树的中序遍历顺序为：左孩子结点 -> 根结点 -> 右孩子结点
template<typename T>
void BinaryTree<T>::InOrder(BinTreeNode<T>*& subTree)
{
    if (subTree != NULL)
    {
        InOrder(subTree->leftChild);
        cout << subTree->data << " ";
        InOrder(subTree->rightChild);
    }
}

//二叉树的后序遍历顺序为：左孩子结点 -> 右孩子结点 -> 根节点
template<typename T>
void BinaryTree<T>::PostOrder(BinTreeNode<T>*& subTree)
{
    if (subTree != NULL) {
        PostOrder(subTree->leftChild);
        PostOrder(subTree->rightChild);
        cout << subTree->data << " ";
    }
}

//非递归层次遍历
template<typename T>
void BinaryTree<T>::LevelOrder(BinTreeNode<T>* p)
{
    queue<BinTreeNode<T>*>Q;
    Q.push(p);
    BinTreeNode<T>* front;
    while (!Q.empty()) {
        front = Q.front();
        Q.pop();
        cout << front->data << " ";

        if (front->leftChild != NULL) {
            Q.push(front->leftChild);
        }
        if (front->rightChild != NULL) {
            Q.push(front->rightChild);
        }
    }

}


//前序遍历的非递归实现
template<typename T>
void BinaryTree<T>::PreOrder_NoRecurve1(BinTreeNode<T>* p)
{
    stack<BinTreeNode<T>*>s;

}
