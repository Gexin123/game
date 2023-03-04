
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "tank.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GAME_WIN_W  (800)
#define GAME_WIN_H  (600)
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
#define MY_STYLE (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | FWS_ADDTOTITLE)
	//创建窗口
	Create(NULL, _T("坦克大战"), MY_STYLE, CRect(0, 0, GAME_WIN_W, GAME_WIN_H));
	{
		CRect rcCli;
		GetClientRect(rcCli);//获取客户区的大小
		//计算边框的大小，并设置
		RECT rcFrame = { 0,0,m_iwidth + m_iwidth - rcCli.right,m_iheight + m_iheight - rcCli.bottom };
		MoveWindow(&rcFrame, TRUE);//调用WindowsAPI设置窗口位置和大小
	}
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetTimer(ETimerIdGameLoop, 0, NULL);//窗口启动的时候就启动定时器
	//
	m_game.SetHandle(GetSafeHwnd());

	return 0;
}
void CMainFrame::OnTimer(UINT_PTR nIDEvent)
{
	switch (nIDEvent)
	{
	case ETimerIdGameLoop: {                              //游戏循环id
		static DWORD dwLastUpdate = GetTickCount64();       //记录本次时刻
		if (GetTickCount64() - dwLastUpdate >= 20) {        //判断时间间隔
			m_game.EnterFrame(GetTickCount64());            //进入游戏帧处理
			dwLastUpdate = GetTickCount64();
		}
	}
	default:
		break;
	}
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	m_game.OnMouseMove(nFlags, point);
	CFrameWnd::OnMouseMove(nFlags, point);
}
void CMainFrame::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_game.OnLButtonUp(nFlags, point);
	CFrameWnd::OnLButtonUp(nFlags, point);
}