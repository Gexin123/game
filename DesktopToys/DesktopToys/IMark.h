//所欲标记类的父类，代表工具类在屏幕上留下的标记
#pragma once
#include "MyDraw.h"
class IMark:public MyDraw
{
public:
	IMark();
	virtual ~IMark();
	virtual bool IsChanging() const = 0;
};

