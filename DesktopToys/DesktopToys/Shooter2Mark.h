#pragma once
#include "IMark.h"
class CShooter2Mark:public IMark
{
public:
	CShooter2Mark(float x, float y);
	virtual ~CShooter2Mark();
	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool IsChanging()const;
private:
	Image* m_img;
	//动态下落的碎片
	typedef struct {
		Image* m_img2;
		PointF m_pos;
		PointF m_speed{ 10.0f,15.0f };
		float m_dir{ 0.0f };
		bool m_bShow{ true };
	}SDynamic;

	std::vector<SDynamic>m_vD;//动态下落的对象数组
};

