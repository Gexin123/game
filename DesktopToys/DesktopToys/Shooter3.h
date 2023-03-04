#pragma once
#include "CShooter.h"
class CShooter3:public CShooter
{
public:
	CShooter3();
	virtual ~CShooter3();
	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool OnLButtonDown(UINT nFlags, CPoint point);
	virtual bool OnLButtonUp(UINT nFlags, CPoint point);
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnRButtonDown(UINT nFlags, CPoint point);
	virtual bool OnRButtonUp(UINT nFlags, CPoint point);
	virtual bool OnRButtonDblClk(UINT nFlags, CPoint point)
	{
		return false;
	}
	virtual bool OnMouseMove(UINT nFlags, CPoint point);

private:
	enum class EStatus {EStatusLeftUp,EStatusLeftDown};
	EStatus m_status{ EStatus::EStatusLeftUp };
	bool m_bRightDown{ false };

	PointF m_mousePos{ 0.0f,0.0f };
	std::vector<Image*>m_vImgUp;
	std::vector<Image*>m_vImgDown;
};

