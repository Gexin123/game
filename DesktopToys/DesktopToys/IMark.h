//���������ĸ��࣬������������Ļ�����µı��
#pragma once
#include "MyDraw.h"
class IMark:public MyDraw
{
public:
	IMark();
	virtual ~IMark();
	virtual bool IsChanging() const = 0;
};

