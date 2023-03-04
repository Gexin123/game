//#include "ScopeGuard.h"
#include "Game.h"
//#include "ScreenTools.h"
#include "pch.h"
#include "IMark.h"

CGame::CGame(HWND hWnd, float x, float y, float w, float h)
	:m_hWnd(hWnd), m_x(x), m_y(y), m_width(w), m_height(h)
	{
	g_game = this;
	m_menu = std::make_shared<CDMenu>(hWnd);//菜单初始化
	{
		RECT r{ (long)x,(long)y,(long)(x + w),(long)(y + h) };
		HBITMAP hBmp = CScreenTools::CopyScreenToBitmap(&r);
		m_imgBk = Bitmap::FromHBITMAP(hBmp, NULL);
	}

	GetClientRect(m_hWnd, &m_rcClient);
}

CGame::~CGame(){}

bool CGame::EnterFrame(DWORD dwTime)
{
	Draw();
	return false;
}

void CGame::OnLButtonDown(UINT nFlags, CPoint point) {
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {//菜单阶段，交给m_menu处理
		if(m_menu->OnLButtonDown(nFlags, point) ){
			break;
		}
		
	}
	case CGame::EGameStatusNormal: {//游戏阶段
		m_pTool->OnLButtonDown(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {//菜单阶段，交给m_menu处理
		if (m_menu->OnLButtonUp(nFlags, point)) {
			break;
		}
	}
	case CGame::EGameStatusNormal: {//游戏阶段
		m_pTool->OnLButtonUp(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

void CGame::OnLButtonDblClk(UINT nFlags, CPoint point)
{

}

void CGame::OnRButtonDown(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {//菜单阶段，交给m_menu处理
		if (m_menu->OnRButtonDown(nFlags, point)) {
			break;
		}
	}
	case CGame::EGameStatusNormal: {//游戏阶段
		m_pTool->OnRButtonDown(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}


void CGame::OnRButtonUp(UINT nFlags, CPoint point)
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {//菜单阶段，交给m_menu处理
		if (m_menu->OnRButtonUp(nFlags, point)) {
			break;
		}
	}
	case CGame::EGameStatusNormal: {//游戏阶段
		m_pTool->OnRButtonUp(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

void CGame::OnRButtonDblClk(UINT nFlags, CPoint point)
{

}

void CGame::OnMouseMove(UINT nFlags, CPoint point) {
	switch (m_eStatus) {
	case CGame::EGameStatusSelect: {//菜单阶段，交给m_menu处理
		break;
	}
	case CGame::EGameStatusNormal: {//游戏阶段
		m_pTool->OnMouseMove(nFlags, point);
		break;
	}
	default: {
		break;
	}
	}
}

BOOL CGame::OnESC()
{
	switch (m_eStatus) {
	case CGame::EGameStatusSelect:
		return FALSE;
	case CGame::EGameStatusNormal:
		m_eStatus = EGameStatusSelect;
		//显示鼠标
		{
			int i = ShowCursor(TRUE);//ShowCursor函数的功能是显示和隐藏鼠标，当其内部的技术大于等于0，则显示。反之则隐藏。
			if (i > 0) {
				while (ShowCursor(FALSE) > 0) {
					;
				}
			}
			else if (i < 0) {
				while (ShowCursor(TRUE < 0)) {
					;
				}
			}
		}
		return TRUE;
	default:
		break;
	}
	return FALSE;
}

void CGame::Draw()
{
	HDC hdc = ::GetDC(m_hWnd);
	//ON_SCOPE_EXIT,离开函数作用域时，释放DC
	ON_SCOPE_EXIT([&]() {
		::ReleaseDC(m_hWnd, hdc);
		});

	CDC* dc = CClientDC::FromHandle(hdc);

	CDC m_dcMemory;//内存DC
	CBitmap bmp;//创建兼容位图对象，并选入内存DC
	bmp.CreateCompatibleBitmap(dc, m_rcClient.Width(), m_rcClient.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* pOldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());
	gh.SetPageScale(Gdiplus::UnitPixel);

	Color clr;
	clr.SetFromCOLORREF(BACK_GROUND_LAYER);
	gh.Clear(clr);
	gh.ResetClip();

	gh.DrawImage(m_imgBk, m_x, m_y, m_width, m_height);


	//合并背景图和不动的元素
	if (!m_vMarks.empty()) {
		Graphics gh(m_imgBk);
		for (auto ptr : m_vMarks) {
			if (!ptr->IsChanging()) {
				ptr->Draw(gh);
			}
		}
		m_vMarks.erase(std::remove_if(m_vMarks.begin(), m_vMarks.end(), [](auto& lhs)->bool {return !lhs->IsChanging(); }), m_vMarks.end());
	}
	//画出继续变动的对象
	for (auto ptr : m_vMarks) {
		ptr->Draw(gh);
	}
	//根据游戏当前的阶段，画不同的东西
	{
		switch (m_eStatus) {
		case CGame::EGameStatusSelect:
			if (m_menu) {
				m_menu->Draw(gh);
			}
			
			break;
		case CGame::EGameStatusNormal:
			if (m_pTool) {
			m_pTool->Draw(gh);
			}

			break;
		default:
			break;

		}
	}
	DrawFps(gh);
	::BitBlt(hdc, 0, 0, m_rcClient.Width(), m_rcClient.Height(), m_dcMemory.GetSafeHdc(), 0, 0, SRCCOPY);//复制到屏幕
	return;
}

void CGame::DrawFps(Gdiplus::Graphics& gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast=GetTickCount();
	if (GetTickCount() - dwLast >= 1000) {
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount();
	}
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);
		SolidBrush brush(Color(0xFF, 0x00, 0x00));
		Gdiplus::Font font(_T("宋体"), 10.0);
		PointF origin(0.0f, 0.0f);
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}