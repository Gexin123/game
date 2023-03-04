#pragma once
using namespace Gdiplus;
#include <gdiplus.h>
class MyDraw
{
public:
	MyDraw();
	virtual ~MyDraw();
	virtual void Draw(Graphics &gh) = 0;
protected:
	RectF m_rect;
public:
	RectF GetRect() const
	{
		return m_rect;
	}
    // 设置自身范围
    void SetRect(RectF& rect)
    {
        m_rect = rect;
    }

    // 设置自身范围
    void SetRect(float X, float Y, float Width, float Height)
    {
        m_rect.X = X;
        m_rect.Y = Y;
        m_rect.Width = Width;
        m_rect.Height = Height;
    }

    // 设置中心点位置
    void SetCenterPos(float x, float y)
    {
        PointF ptCenter(x, y);
        SetCenterPos(ptCenter);
    }

    // 设置中心点位置
    void SetCenterPos(const PointF& ptCenter)
    {
        RectF r = m_rect;
        r.X = ptCenter.X - r.Width / 2.0f;
        r.Y = ptCenter.Y - r.Height / 2.0f;
        SetRect(r);
    }

    // 获得中心点位置
    PointF GetcenterPos()
    {
        PointF pt = PointF(m_rect.X + m_rect.Width / 2.0f, m_rect.Y + m_rect.Height / 2.0f);
        //pt.X = m_rect.X + m_rect.Width / 2.0f;
        //pt.Y = m_rect.Y + m_rect.Height / 2.0f;
        return pt;
    }

    // 设置大小
    void SetSize(float w, float h)
    {
        PointF ptCenter = GetcenterPos();
        RectF rr = m_rect;
        rr.Width = w;
        rr.Height = h;
        SetRect(rr);
        SetCenterPos(ptCenter);
    }
};
