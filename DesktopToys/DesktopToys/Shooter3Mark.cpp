#include "pch.h"
#include "Shooter3Mark.h"
CShooter3Mark::CShooter3Mark(float x, float y)
{
	SetCenterPos(x, y);
	srand(time(0));
	int i = 1 + rand() % 5;
	TCHAR szFilename[MAX_PATH] = { 0 };
	_stprintf_s(szFilename, _T("res/Eraser Ed Marks %02d.png", i),1);
	m_img = Image::FromFile(szFilename);
	//m_img = Image::FromFile(_T("res/Eraser Ed Marks 01.png"));
	m_degree = (float)(rand() % 360);

	for (int i = 0; i < (1 + rand() % 3); ++i) {
		SDynamic dy;
		dy.m_img2 = Image::FromFile(_T("res/Eraser Ed Marks 06.png"));

		dy.m_speed = PointF(float(rand() % 10 - 5), float(rand() % 10 - 5));

		dy.m_pos.X = x + float(rand() % 80 - 40);
		dy.m_pos.Y = y + float(rand() % 80 - 40);

		dy.m_dir = Drgree2Radian(rand() % 360);

		dy.m_bShow = true;
		m_vD.push_back(dy);
	}
}

CShooter3Mark::~CShooter3Mark(){}

static void DrawImageRotate(PointF mousePos, Graphics& gh, Image* img, float degree)
{
	PointF center = mousePos;
	center.X += img->GetWidth() / 2.0f;
	center.Y += img->GetHeight() / 2.0f;

	gh.TranslateTransform(center.X, center.Y);
	gh.RotateTransform(degree);
	gh.TranslateTransform(-center.X, -center.Y);
	ON_SCOPE_EXIT([&]() {
		gh.TranslateTransform(center.X, center.Y);
		gh.RotateTransform(-degree);
		gh.TranslateTransform(-center.X, -center.Y);
		});

	{
		RectF rc;
		rc.X = mousePos.X;
		rc.Y = mousePos.Y;
		rc.Width = (float)img->GetWidth();
		rc.Height = (float)img->GetHeight();
		gh.DrawImage(img, rc);
	}

}

void CShooter3Mark::Draw(Gdiplus::Graphics& gh)
{
	gh.DrawImage(m_img, GetcenterPos());
	//画下落的物体
	for (auto& dy : m_vD) {
		if (dy.m_bShow) {
			//判断物体是否落到屏幕的外面
			/*
			RectF::Contains方法确定点是否在此矩形内
			BOOL Contains(
  [in] const PointF & pt
);
			*/
			if (!g_game->GetrectF().Contains(dy.m_pos)) {
				continue;
			}
			DrawImageRotate(dy.m_pos, gh, dy.m_img2, Radian2Degree(dy.m_dir));
			{
				//调整位置
				dy.m_pos.X += dy.m_speed.X;
				dy.m_pos.Y += dy.m_speed.Y;
				dy.m_speed.Y += 1.0f;
				dy.m_dir += PI(0.1f);
				if (dy.m_dir >= PI(2.0f)) {
					dy.m_dir = 0.0f;
				}
			}
		}
	}
	//移除落到游戏窗口外面的物体
	/*
	把要删除的元素移到容器末尾并返回要被删除元素的迭代器，然后通过erase成员函数来真正删除
	最后一个参数：传入一个回调函数，如果回调函数返回为真，则将当前所指向的参数移到尾部。
	*/
	m_vD.erase(std::remove_if(m_vD.begin(), m_vD.end(), [&](auto& lhs)->bool {
		return (!g_game->GetrectF().Contains(lhs.m_pos));
		}), m_vD.end());
}

bool CShooter3Mark::IsChanging() const
{
	return !m_vD.empty();
}
