
// MainFrm.h: CMainFrame 类的接口
//

#pragma once
#include"Game.h"

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame() noexcept;

protected: // 仅从序列化创建
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:

// 实现
public:
	virtual ~CMainFrame();

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	
	int m_iwidth{ 800 };
	int m_iheight{ 600 };
	enum ETimerId{ETimerIdGameLoop=1};//定时器id
	CGame m_game;                     //游戏对象
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


