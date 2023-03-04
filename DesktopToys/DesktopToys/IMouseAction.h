//所有需要处理鼠标消息的类都要继承本类，并对自己感兴趣的鼠标消息进行处理
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

