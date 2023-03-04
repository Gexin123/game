#include "pch.h"
#include "GameMenuBackground.h"
#include "Game.h"

CGameMenuBackground::CGameMenuBackground()
{
	m_imgBackground = Image::FromFile(_T("menu_background.png"));
}


CGameMenuBackground::~CGameMenuBackground()
{

}

void CGameMenuBackground::Draw(Graphics& gh)const
{
	gh.DrawImage(m_imgBackground, m_rect);
}