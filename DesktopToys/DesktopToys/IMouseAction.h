//������Ҫ���������Ϣ���඼Ҫ�̳б��࣬�����Լ�����Ȥ�������Ϣ���д���
#pragma once
class IMouseAction
{
public:
	IMouseAction();
	virtual ~IMouseAction();

	virtual bool OnLButtonDown(UINT nFlags, CPoint point) { return false; }
	virtual bool OnLButtonUp(UINT nFlags, CPoint point) { return false; }
	virtual bool OnLButtonDblClk(UINT nFlags, CPoint point) { return false; }
	virtual bool OnRButtonDown(UINT nFlags, CPoint point) { return false; }
	virtual bool OnRButtonUp(UINT nFlags, CPoint point) { return false; }
	virtual bool OnRButtonDblClk(UINT nFlags, CPoint point) { return false; }
	virtual bool OnMouseMove(UINT nFlags, CPoint point) { return false; }
};

