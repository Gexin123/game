#include "pch.h"
#include "Shooter0.h"
#include "Shooter0Mark.h"
#include<cmath>

CShooter0::CShooter0()
{
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 静.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左上.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 左下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero 右下.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Fire Path.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 00.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 01.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 02.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 03.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Left Fire 04.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 00.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 01.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 02.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 03.png")));
	m_vImage.push_back(Image::FromFile(_T("res/Foton The Desktop Hero Right Fire 04.png")));

	RectF rc;
	rc.Width = (float)m_vImage[0]->GetWidth();
	rc.Height = (float)m_vImage[0]->GetHeight();
	rc.X = 800.0f;
	rc.Y = 600.0f;
	SetRect(rc);
}

CShooter0::~CShooter0(){}

void CShooter0::Draw(Gdiplus::Graphics& gh)
{
	switch (m_eStatus) {
		//当前的初始状态，人物微微的晃动
	case EStatus0: {
		m_index = 0;
		if (m_timer0.IsTimeval()) {
			m_bUp = !m_bUp;
			if (m_bUp) {
				auto pt = GetcenterPos();
				pt.Y += 1.0f;
				SetCenterPos(pt);
			}
			else {
				auto pt = GetcenterPos();
				pt.Y -= 1.0f;
				SetCenterPos(pt);
			}
		}
		gh.DrawImage(m_vImage[m_index], GetRect());
		break;
		}
	case EStatusMove0: {
		m_index = 1 + (EStatusMove0 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove1: {
		m_index = 1 + (EStatusMove1 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove2: {
		m_index = 1 + (EStatusMove2 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove3: {
		m_index = 1 + (EStatusMove3 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove4: {
		m_index = 1 + (EStatusMove4 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove5: {
		m_index = 1 + (EStatusMove5 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove6: {
		m_index = 1 + (EStatusMove6 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusMove7: {
		m_index = 1 + (EStatusMove7 - EStatusMove0);
		gh.DrawImage(m_vImage[m_index], GetRect());
		DrawMove(gh);
		break;
	}
	case EStatusFireLeft:{
		DrawFire(gh);
		break;
	}
	case EStatusFireRight: {
		DrawFire(gh);
		break;
	}
	default:
		break;
	}
}


void CShooter0::DrawMove(Gdiplus::Graphics& gh)
{
	//只是更新位置，直到到达为止

	//如果到达，更新状态
	if (GetRect().Contains(m_moveTo)) {
		m_eStatus = EStatus0;
		return;
	}
	//否则移动忍者的位置
	PointF pt = GetcenterPos();
	pt.X += 20.0f * cos(PI(2.0f) - m_moveDir);
	pt.Y += 20.0f * sin(PI(2.0f) - m_moveDir);
	SetCenterPos(pt);
}


void CShooter0::DrawFire(Gdiplus::Graphics& gh)
{
	switch (m_eStatus) {
	case EStatusFireLeft: {
		switch (m_index_fire) {
		case 0: {
			auto img = m_vImage[10];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
		// 聚集能量
		case 1: {
			auto img = m_vImage[11];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
			  //聚集能量
		case 2: {
			auto img = m_vImage[12];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
			  //发射子弹
		case 3: {
			g_game->Append(std::make_shared<CShooter0Mark>(m_fireTo.X, GetRect().Y));
		}
			  //发射激光
		case 4: {
			const float Y = GetRect().Y;
			const float X = GetRect().X;
			const float YY = Y;
			const float XX = m_fireTo.X + 30.0f;
			//画忍者的身体和动作
			{
				auto img = m_vImage[13];
				gh.DrawImage(img, X, Y);
			}
			//画中间的激光部分
			{
				auto img = m_vImage[9];
				float left = X + 52;
				//拼接图片进行输出，因为中间部分的长度不能确定，不能一开始就确定图片的长度
				while (left >= (XX + 60.0f)) {
					gh.DrawImage(img,left, Y, (float)img->GetWidth(), (float)img->GetHeight());
					left -= (-2.0f + (float)img->GetWidth());
				}
			}
			//画出击中的部分
			{
				auto img = m_vImage[14];
				gh.DrawImage(img, XX, Y);
			}
			break;
		}
			  //再转身回去
		case 5: {
			auto img = m_vImage[10];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
		case 6: {
			m_eStatus = EStatus0;
			return;
		}
		default:break;
		}
		break;
	}
	case EStatusFireRight: {
		switch (m_index_fire) {
		case 0: {
			auto img = m_vImage[15];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
			  // 聚集能量
		case 1: {
			auto img = m_vImage[16];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
			  //聚集能量
		case 2: {
			auto img = m_vImage[17];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
			  //发射子弹
		case 3: {
			g_game->Append(std::make_shared<CShooter0Mark>(m_fireTo.X, GetRect().Y));
		}
			  //发射激光
		case 4: {
			const float Y = GetRect().Y;
			const float X = GetRect().X;
			const float YY = Y;
			const float XX = m_fireTo.X + 30.0f;
			//画忍者的身体和动作
			{
				auto img = m_vImage[18];
				gh.DrawImage(img, X, Y, (float)m_vImage[18]->GetWidth(), (float)m_vImage[18]->GetHeight());
			}
			//画中间的激光部分
			{
				auto img = m_vImage[9];
				float left = X + 50;
				//拼接图片进行输出，因为中间部分的长度不能确定，不能一开始就确定图片的长度
				while (left <= (XX) ){
					gh.DrawImage(img, left, Y + 4, (float)img->GetWidth(), (float)img->GetHeight());
					left += (-2.0f + (float)img->GetWidth());
				}
			}
			//画出击中的部分
			{
				auto img = m_vImage[19];
				gh.DrawImage(img, XX, Y, (float)m_vImage[19]->GetWidth(), (float)m_vImage[19]->GetHeight());
			}
			break;
		}
			  //再转身回去
		case 5: {
			auto img = m_vImage[15];
			RectF r = GetRect();
			r.Width = (float)img->GetWidth();
			r.Height = (float)img->GetHeight();
			gh.DrawImage(img, r);
			break;
		}
		case 6: {
			m_eStatus = EStatus0;
			return;
		}

		default:
			break;
		}
		break;
	}
	default:break;
	}

	//判断状态
	if (m_timerFire.IsTimeval()) {
		int times = m_timerFire.GetTimes();
		if (times > 6) {
			m_index_fire = 6;
		}
		else if (times > 5) {
			m_index_fire = 5;
		}
		else if (times > 4) {
			m_index_fire = 4;
		}
		else if (times > 3) {
			m_index_fire = 3;
		}
		else if (times > 2) {
			m_index_fire = 2;
		}
		else if (times > 1) {
			m_index_fire = 1;
		}
		else if (times > 0) {
			m_index_fire = 0;
		}
	}
}
//处理鼠标的消息
bool CShooter0::OnLButtonDown(UINT nFlags, CPoint point)
{
	PointF ptCenter = GetcenterPos();
	PointF ptDest(static_cast<float>(point.x), static_cast<float>(point.y));
	m_moveTo = ptDest;
	float theta = std::atan2<float> (-(ptDest.Y - ptCenter.Y), ptDest.X - ptCenter.X);
	if (theta < 0.0f) {
		theta = PI(2.0f) + theta;
	}

	m_moveDir =theta;

	//平面直角坐标系分成8份，当角度落在某个区间时，分别处理
	float a_per = PI(2.0f / 8.0f);
	float a_per_half = (a_per / 2.0f);
	float a_start = -a_per_half;
	int i = 0;
	for (; i < 7; i++)
	{
		float min = a_start + i * a_per;
		float max = a_start + (1 + i) * a_per;
		if (min <= theta && theta < max) {
			m_eStatus = (EStatus)(i + EStatusMove0);
			break;
		}
	}
	if (i == 7) {
		m_eStatus = (EStatus)(i + EStatusMove0);
		return true;
	}
	return false;
}

bool CShooter0::OnRButtonDown(UINT nFlags, CPoint point) {
	PointF ptCenter = GetcenterPos();
	PointF ptDest(static_cast<float>(point.x), static_cast<float>(point.y));
	m_fireTo = ptDest;
	if (ptDest.X > ptCenter.X) {
		m_eStatus = EStatusFireRight;
	}
	else {
		m_eStatus = EStatusFireLeft;
	}
	m_timerFire.Restart();
	m_index_fire = 0;
	return true;
}