#include "pch.h"
#include "DesktopToys.h"
//#include "DesktopToysDlg.h"
#include "afxdialogex.h"
// DesktopToysDlg.h: 头文件
//

#pragma once


// CDesktopToysDlg 对话框
class CDesktopToysDlg : public CDialogEx
{
// 构造
public:
	CDesktopToysDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DESKTOPTOYS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual BOOL PreTanslateMessage(MSG *pMsg);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//所有的游戏功能都发送给CGame对象来完成
private:
	std::shared_ptr<CGame> m_pGame;
};
