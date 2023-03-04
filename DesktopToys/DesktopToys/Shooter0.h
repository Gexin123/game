#pragma once
#include "CShooter.h"
#include "GameTimer.h"
//忍者类
class CShooter0:public CShooter
{
public:
	CShooter0();
	virtual ~CShooter0();
	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDblClk(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnMouseMove(UINT nFlags, CPoint point)
	{
		return false;
	}
private:
	std::vector<Image*>m_vImage;
	typedef enum {
		EStatus0=0,
		EStatusMove0,
		EStatusMove1,
		EStatusMove2,
		EStatusMove3,
		EStatusMove4,
		EStatusMove5,
		EStatusMove6,
		EStatusMove7,
		EStatusFireLeft,
		EStatusFireRight,

	}EStatus;
	EStatus m_eStatus{ EStatus0 };
	size_t m_index{ 0 };//当前显示的图片
	CGameTimeval m_timer0{ 500 };//没有动作时，上下晃动
	bool m_bUp{ false };//记录当前是向上还是向下

	//向某方向上移动，开始移动，到达后恢复静止状态
	void DrawMove(Gdiplus::Graphics& gh);
	PointF m_moveTo;//鼠标右键单击的位置
	float m_moveDir;

	/*
	开火动画处理：一共有4帧动画
	0原地转身
	1聚集能量
	2聚集能量
	3射击开始
	4击中
	*/
	CGameTimeval m_timerFire{ 100 };
	size_t m_index_fire{ 0 };
	void DrawFire(Gdiplus::Graphics& gh);
	PointF m_fireTo;
};

