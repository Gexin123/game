
// tankView.cpp: CtankView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "tank.h"
#endif

#include "tankDoc.h"
#include "tankView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtankView

IMPLEMENT_DYNCREATE(CtankView, CView)

BEGIN_MESSAGE_MAP(CtankView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CtankView 构造/析构

CtankView::CtankView() noexcept
{
	// TODO: 在此处添加构造代码

}

CtankView::~CtankView()
{
}

BOOL CtankView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CtankView 绘图

void CtankView::OnDraw(CDC* /*pDC*/)
{
	CtankDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CtankView 打印

BOOL CtankView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CtankView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CtankView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CtankView 诊断

#ifdef _DEBUG
void CtankView::AssertValid() const
{
	CView::AssertValid();
}

void CtankView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtankDoc* CtankView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtankDoc)));
	return (CtankDoc*)m_pDocument;
}
#endif //_DEBUG


// CtankView 消息处理程序
