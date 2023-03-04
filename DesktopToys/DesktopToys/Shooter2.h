#pragma once
#include "CShooter.h"
class CShooter2:public CShooter
{
public:
	CShooter2();
	virtual ~CShooter2();
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
	//当前工具
	enum class EStatus{EStatusHammer,EstatusSaw};
	EStatus m_status{ EStatus::EStatusHammer };

	//锤子状态
	enum class EStatusHammer{EStatusHammerDownFirst,EStatusHammerDown,EStatusHammerUp};
	EStatusHammer m_StatusHammer{ EStatusHammer::EStatusHammerDown };

	//电锯状态
	enum class EStatusSaw{ EStatusSawStart,EStatusMoving,EStatusSawStop};
	EStatusSaw m_StatusSaw{ EStatusSaw::EStatusSawStop };

	float m_sawSpeed{ 10.0f };
	float m_sawDegree{ 0.0f };
	PointF m_sawPos{ 0.0f,0.0f };
	PointF m_mousePosLast{ 0.0f,0.0f };
	PointF m_mousePos{ 0.0f,0.0f };

	Image* m_img0;
	Image* m_img1;
	Image* m_img2;

	Gdiplus::Font m_font{ L"宋体",20.0f };
	SolidBrush m_brush{ Color::Red };
};

