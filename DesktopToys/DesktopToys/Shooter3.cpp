#include "pch.h"
#include "Shooter3.h"
#include "Shooter3Mark.h"
#include "GameTimer.h"

CShooter3::CShooter3()
{
	m_vImgUp.push_back(Image::FromFile(_T("res/Eraser Ed 0.png")));
	m_vImgUp.push_back(Image::FromFile(_T("res/Eraser Ed 1.png")));
	m_vImgUp.push_back(Image::FromFile(_T("res/Eraser Ed 2.png")));
	m_vImgDown.push_back(Image::FromFile(_T("res/Eraser Ed 00.png")));
	m_vImgDown.push_back(Image::FromFile(_T("res/Eraser Ed 01.png")));
}
CShooter3::~CShooter3(){}

void CShooter3::Draw(Gdiplus::Graphics& gh)
{
	switch (m_status) {
	case CShooter3::EStatus::EStatusLeftUp: {
		if (!m_bRightDown) {
			//反复显示三幅图片：达到眨眼的操作
			static size_t index = 0;
			if (index >= 3) {
				index = 0;
			}
			//画当前的图片
			{
				auto img = m_vImgUp[index];
				RectF rc;
				rc.X = m_mousePos.X;
				rc.Y = m_mousePos.Y;
				rc.Width = (float)img->GetWidth();
				rc.Height = (float)img->GetHeight();
				gh.DrawImage(img, rc);
			}
			static CGameTimeval val(200);
			if (val.IsTimeval()) {
				index++;
			}
			if (index == 2) {
				if (0 == rand() % 4) {

				}
				else {
					index = 0;
				}
			}
		}
		else {
			size_t index = 2;
			{
				auto img = m_vImgUp[index];
				RectF rc;
				rc.X = m_mousePos.X;
				rc.Y = m_mousePos.Y;
				rc.Width = (float)img->GetWidth();
				rc.Height = (float)img->GetHeight();
				gh.DrawImage(img, rc);
			}
		}
		break;
	}
	case CShooter3::EStatus::EStatusLeftDown: {
		static size_t index = 0;
		if (index > 1) {
			index = 0;
		}
		auto img = m_vImgDown[index];
		RectF rc;
		rc.X = m_mousePos.X;
		rc.Y = m_mousePos.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
		if (index == 1) {
			g_game->Append(std::make_shared<CShooter3Mark>(m_mousePos.X, m_mousePos.Y));
		}
		static CGameTimeval val(30);
		if (val.IsTimeval()) {
			index++;
		}
		break;
	}
	default:
		break;
	}
}

bool CShooter3::OnLButtonDown(UINT nFlags, CPoint point) {
	m_status = EStatus::EStatusLeftDown;
	return true;
}

bool CShooter3::OnLButtonUp(UINT nFlags, CPoint point) {
	m_status = EStatus::EStatusLeftUp;
	return true;
}

bool CShooter3::OnRButtonDown(UINT nFlags, CPoint point)
{
	m_bRightDown = true;
	return true;
}

bool CShooter3::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_bRightDown = false;
	return true;
}

bool CShooter3::OnMouseMove(UINT nFlags, CPoint point)
{
	m_mousePos.X = (float)point.x;
	m_mousePos.Y = (float)point.y;
	return true;
}