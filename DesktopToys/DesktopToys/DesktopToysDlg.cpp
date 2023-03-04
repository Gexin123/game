﻿
// DesktopToys2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "DesktopToys.h"
#include "DesktopToysDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDesktopToys2Dlg 对话框



CDesktopToysDlg::CDesktopToysDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DESKTOPTOYS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDesktopToysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDesktopToysDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDesktopToys2Dlg 消息处理程序
Image* bmp = nullptr;
BOOL CDesktopToysDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	{
	int w = GetSystemMetrics(SM_CXSCREEN);
	int y = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(0, 0, w, y,TRUE);

	//RECT r{ 0,0,100,300 };
	//HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
	//bmp = Bitmap::FromHBITMAP(hBmp, NULL);

	m_pGame = std::make_shared<CGame>(GetSafeHwnd(), 0.0f, 0.0f, float(w), float(y));
	SetTimer(1, 10, nullptr);
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDesktopToysDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		HDC hdc = ::GetDC(GetSafeHwnd());
		Gdiplus::Graphics gh(hdc);
		gh.DrawImage(bmp, Rect(0, 0, 100, 300));
		::ReleaseDC(GetSafeHwnd(), hdc);
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDesktopToysDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CDesktopToysDlg::PreTanslateMessage(MSG* pMsg)
{
	//按下退出键的时候也进行的处理
	if (pMsg->message== WM_KEYDOWN && pMsg->wParam == VK_ESCAPE){
		if (m_pGame->OnESC()) {
			return TRUE;
		}
		else {
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}



void CDesktopToysDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	m_pGame->OnLButtonDown(nFlags, point);
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDesktopToysDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//AfxMessageBox(_T("鼠标左键抬起消息"));
	m_pGame->OnLButtonUp(nFlags, point);
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDesktopToysDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnRButtonDown(nFlags, point);
	CDialogEx::OnRButtonDown(nFlags, point);
}


void CDesktopToysDlg::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnRButtonUp(nFlags, point);
	CDialogEx::OnRButtonUp(nFlags, point);
}


void CDesktopToysDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->OnMouseMove(nFlags, point);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDesktopToysDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_pGame->EnterFrame(0);
	CDialogEx::OnTimer(nIDEvent);
}
