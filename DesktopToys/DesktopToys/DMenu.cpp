#include "pch.h"
#include "DMenu.h"
#include "CShooter.h"
#include "Shooter0.h"
#include "Shooter1.h"
#include "Shooter2.h"
#include "Shooter3.h"

CDMenu::CDMenu(HWND hWnd) :m_hWnd(hWnd)
{
	//载入菜单子项
	m_box = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center01.png"), _T(""));
	m_cover = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center02.png"), _T(""));
	m_cover2 = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/Menu Center02.png"), _T(""));
	m_item0 = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem00.png"), _T("我是忍者"));
	m_item1 = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem01.png"), _T("粉刷匠"));
	m_item2 = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem02.png"), _T("锤子"));
	m_item3 = std::make_shared<CMenuItem>(100.0f, 100.0f, _T("res/MenuItem03.png"), _T("橡皮"));

	{
		RECT rc;
		GetWindowRect(m_hWnd, &rc);
		PointF pt((rc.right - rc.left) / 2.0f, (rc.bottom - rc.top) / 2.0f);
		SetCenterPos(pt);
	}
	InitAnimateInfo0();
}

CDMenu::~CDMenu()
{

}

void CDMenu::InitAnimateInfo0()
{
	RECT rc;
	GetWindowRect(m_hWnd, &rc);
	PointF pt = GetcenterPos();
	m_box->SetCenterPos(pt);
	m_item0->SetCenterPos(pt);
	m_item1->SetCenterPos(pt);
	m_item2->SetCenterPos(pt);
	m_item3->SetCenterPos(pt);

	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover->SetCenterPos(pt2);
	}
	{
		PointF pt2 = pt;
		pt2.Y -= 30;
		m_cover2->SetCenterPos(pt2);
	}

	//初始化动画信息
	m_box->InitAnimateInfo3(pt.X, pt.Y);
	m_cover->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	m_item0->InitAnimateInfo0(pt.X, pt.Y, 0.0f);
	m_item1->InitAnimateInfo0(pt.X, pt.Y, PI(0.5f));
	m_item2->InitAnimateInfo0(pt.X, pt.Y, PI(1.0f));
	m_item3->InitAnimateInfo0(pt.X, pt.Y, PI(1.5f));
	//初始化动画信息
	m_cover2->InitAnimateInfo1(pt.X, pt.Y - 100, PI(0.5f));
	m_cover2->InitAnimateInfoReverse();
}

void CDMenu::Draw(Gdiplus::Graphics& gh)
{
	switch (m_eStatus) {
	case EStatusOverCover1: {
		PointF pt = GetcenterPos();
		if (m_cover->IsAnimateEnd()) {
			m_eStatus = EStatusItem0;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		break;
	}
	case EStatusItem0: {
		if (m_item0->IsAnimateEnd()) {
			m_eStatus = EStatusItem1;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		break;
	}
	case EStatusItem1: {
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusItem2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		break;
	}
	case EStatusItem2: {
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusItem3;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		break;
	}
	case EStatusItem3: {
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusOverCover2;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusOverCover2: {
		if (m_item1->IsAnimateEnd()) {
			m_eStatus = EStatusAll;
			break;
		}
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	case EStatusAll: {
		m_box->Draw(gh);
		m_cover->Draw(gh);
		m_item0->Draw(gh);
		m_item1->Draw(gh);
		m_item2->Draw(gh);
		m_item3->Draw(gh);
		break;
	}
	default:
		break;
	}
}

void CDMenu::EndAnimate()
{
	m_eStatus = EStatusAll;
	m_item0->EndAnimate();
	m_item1->EndAnimate();
	m_item2->EndAnimate();
	m_item3->EndAnimate();
	m_cover->EndAnimate();
	m_cover2->EndAnimate();
}

bool CDMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_item0->OnLButtonDown(nFlags, point)) {
		EndAnimate();
		//AfxMessageBox(_T("设置游戏进入游戏阶段，并设置当前工具为CShooter0"));
		g_game->SetStatusNormal(std::make_shared<CShooter0>(), TRUE);
		return true;
	}
	if (m_item1->OnLButtonDown(nFlags, point)) {
		EndAnimate();
		RECT rc;
		GetClientRect(m_hWnd, &rc);
		//AfxMessageBox(_T("设置游戏进入游戏阶段，并设置当前工具为CShooter1"));
		g_game->SetStatusNormal(std::make_shared<CShooter1>(static_cast<int>(rc.bottom - rc.top)), FALSE);
		return true;
	}
	if (m_item2->OnLButtonDown(nFlags, point)) {
		EndAnimate();
		//AfxMessageBox(_T("设置游戏进入游戏阶段，并设置当前工具为CShooter2"));
		g_game->SetStatusNormal(std::make_shared<CShooter2>(), FALSE);
		return true;
	}
	if (m_item3->OnLButtonDown(nFlags, point)) {
		EndAnimate();
		//AfxMessageBox(_T("设置游戏进入游戏阶段，并设置当前工具为CShooter3"));
		g_game->SetStatusNormal(std::make_shared<CShooter3>(), FALSE);
		return true;
	}
	return false;
}

bool CDMenu::OnRButtonDown(UINT nFlags, CPoint point)
{
	return false;
}

bool CDMenu::OnMouseMove(UINT nFlags, CPoint point)
{
	//调用各个菜单的函数，把鼠标消息转发过去，使得各个菜单子项各自处理
	if (m_item0->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item1->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item2->OnMouseMove(nFlags, point)) {
		return true;
	}
	if (m_item3->OnMouseMove(nFlags, point)) {
		return true;
	}
	return false;
}