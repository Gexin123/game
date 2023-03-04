//所有工具类的父类
#pragma once
#include "MyDraw.h"
#include "IMouseAction.h"
class CShooter:public MyDraw,public IMouseAction
{
public:
	CShooter();
	virtual ~CShooter();

};

