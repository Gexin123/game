#pragma once
#include "CShooter.h"
class CShooter1 :public CShooter
{
public:
	CShooter1(int height);
	virtual ~CShooter1();
	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
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
	virtual bool OnMouseMove(UINT nFlags, CPoint point);
private:
	int m_nHeight{ 1024 };
	//0：梯子，1：右，2：右回头，3：左，4：左回头，5：粉刷
	int m_status{ 1 };
	int m_statusLast{ 1 };
	PointF m_mousePos{ 0.0f,0.0f };
	PointF m_mousePosLast{ 0.0f,0.0f };
	PointF m_lastChangePos{ 0.0f,0.0f };
	const float m_distancaChange{ 23.0f };
	int m_iColorIndex{ 0 };
	Image* m_img0;
	Image* m_img1; 
	Image* m_img2;
	Image* m_img3;
	Image* m_img4;
	Image* m_img5;
};

