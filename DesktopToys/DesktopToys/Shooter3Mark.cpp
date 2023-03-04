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
	//�����������
	for (auto& dy : m_vD) {
		if (dy.m_bShow) {
			//�ж������Ƿ��䵽��Ļ������
			/*
			RectF::Contains����ȷ�����Ƿ��ڴ˾�����
			BOOL Contains(
  [in] const PointF & pt
);
			*/
			if (!g_game->GetrectF().Contains(dy.m_pos)) {
				continue;
			}
			DrawImageRotate(dy.m_pos, gh, dy.m_img2, Radian2Degree(dy.m_dir));
			{
				//����λ��
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
	//�Ƴ��䵽��Ϸ�������������
	/*
	��Ҫɾ����Ԫ���Ƶ�����ĩβ������Ҫ��ɾ��Ԫ�صĵ�������Ȼ��ͨ��erase��Ա����������ɾ��
	���һ������������һ���ص�����������ص���������Ϊ�棬�򽫵�ǰ��ָ��Ĳ����Ƶ�β����
	*/
	m_vD.erase(std::remove_if(m_vD.begin(), m_vD.end(), [&](auto& lhs)->bool {
		return (!g_game->GetrectF().Contains(lhs.m_pos));
		}), m_vD.end());
}

bool CShooter3Mark::IsChanging() const
{
	return !m_vD.empty();
}
