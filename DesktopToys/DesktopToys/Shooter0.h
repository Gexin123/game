#pragma once
#include "CShooter.h"
#include "GameTimer.h"
//������
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
	size_t m_index{ 0 };//��ǰ��ʾ��ͼƬ
	CGameTimeval m_timer0{ 500 };//û�ж���ʱ�����»ζ�
	bool m_bUp{ false };//��¼��ǰ�����ϻ�������

	//��ĳ�������ƶ�����ʼ�ƶ��������ָ���ֹ״̬
	void DrawMove(Gdiplus::Graphics& gh);
	PointF m_moveTo;//����Ҽ�������λ��
	float m_moveDir;

	/*
	���𶯻�����һ����4֡����
	0ԭ��ת��
	1�ۼ�����
	2�ۼ�����
	3�����ʼ
	4����
	*/
	CGameTimeval m_timerFire{ 100 };
	size_t m_index_fire{ 0 };
	void DrawFire(Gdiplus::Graphics& gh);
	PointF m_fireTo;
};

