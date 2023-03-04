#pragma once
#include<tuple>
#include<vector>
#include "GameEntry.h"
using namespace std;

class CGame;
class CGameMenuPanel:public CGameEntryMoveable
{
public:
	CGameMenuPanel();
	~CGameMenuPanel();

	void SetParent(CGame* g)
	{
		m_pParent = g;
	};
	CGame *m_pParent{ nullptr };
	virtual void Draw(Graphics& gh)const;//画自己 
	RectF m_rect{ 0,0,800,600 };
	void OnMouseMove(UINT nFlags, CPoint point);//处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point);//处理左键抬起事件
	Image *m_imgBackground;
	struct {
		vector<tuple<Image*, RectF>>vImageInfoptr;//图片的指针和范围
		int index;
	}m_menuItems[2];
};

