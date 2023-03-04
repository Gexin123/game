#pragma once
#include "MyDraw.h"
#include "IMouseAction.h"
#include "MenuItem.h"
//#include "MenuItem.h"
//选择工具的菜单界面
class CDMenu:public MyDraw,public IMouseAction
{
public:
	CDMenu(HWND hWnd);
	virtual ~CDMenu();
	void InitAnimateInfo0();
	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnMouseMove(UINT nFlags, CPoint point);

private:
	HWND m_hWnd;
	std::shared_ptr<CMenuItem>m_box;//盒子
	std::shared_ptr<CMenuItem>m_cover;//盒盖1，打开
	std::shared_ptr<CMenuItem>m_cover2;//盒盖2，关闭
//选项,四个小工具
	std::shared_ptr<CMenuItem>m_item0;
	std::shared_ptr<CMenuItem>m_item1;
	std::shared_ptr<CMenuItem>m_item2;
	std::shared_ptr<CMenuItem>m_item3;
	void EndAnimate();
	typedef enum {EStatusOverCover1,
	EStatusItem0,
		EStatusItem1,
		EStatusItem2,
		EStatusItem3,
		EStatusOverCover2,
		EStatusAll
	}EStatus;
	EStatus m_eStatus{ EStatusOverCover1 };
public:

};

