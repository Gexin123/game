//���й�����ĸ���
#pragma once
#include "MyDraw.h"
#include "IMouseAction.h"
class CShooter:public MyDraw,public IMouseAction
{
public:
	CShooter();
	virtual ~CShooter();

};

