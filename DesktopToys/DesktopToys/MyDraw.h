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
    // ��������Χ
    void SetRect(RectF& rect)
    {
        m_rect = rect;
    }

    // ��������Χ
    void SetRect(float X, float Y, float Width, float Height)
    {
        m_rect.X = X;
        m_rect.Y = Y;
        m_rect.Width = Width;
        m_rect.Height = Height;
    }

    // �������ĵ�λ��
    void SetCenterPos(float x, float y)
    {
        PointF ptCenter(x, y);
        SetCenterPos(ptCenter);
    }

    // �������ĵ�λ��
    void SetCenterPos(const PointF& ptCenter)
    {
        RectF r = m_rect;
        r.X = ptCenter.X - r.Width / 2.0f;
        r.Y = ptCenter.Y - r.Height / 2.0f;
        SetRect(r);
    }

    // ������ĵ�λ��
    PointF GetcenterPos()
    {
        PointF pt = PointF(m_rect.X + m_rect.Width / 2.0f, m_rect.Y + m_rect.Height / 2.0f);
        //pt.X = m_rect.X + m_rect.Width / 2.0f;
        //pt.Y = m_rect.Y + m_rect.Height / 2.0f;
        return pt;
    }

    // ���ô�С
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
