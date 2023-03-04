#pragma once
#include "IMark.h"
class CShooter0Mark:public IMark
{
public:
	CShooter0Mark(float x, float y);
	virtual ~CShooter0Mark();

	virtual void Draw(Gdiplus::Graphics& gh);
	virtual bool IsChanging() const;
private:
	std::vector<Image*>m_img;
	size_t m_index{ 0 };//�ڼ���ͼƬ
	float m_dir;//��ת�ĽǶ�
};

