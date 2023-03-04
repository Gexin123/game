#include "pch.h"
#include "Game.h"
#include<algorithm>
#define KEYDOWN(vk)(GetAsyncKeyState(vk) & 0x8000)
CGame::CGame()
{
	GameInitOne2Bot();
	m_menuselect.m_pParent = this;
	m_menubackup.m_pParent = this;
}
CGame::~CGame()
{

}
void CGame::SetHandle(HWND hwnd)
{
	m_hwnd = hwnd;
}
bool CGame::EnterFrame(DWORD dwTime)
{
	GameRunDraw();
	GameRunLogic();
	return false;
}

//处理鼠标移动事件
void CGame::OnMouseMove(UINT nFlags, CPoint point)
{
	//选择阶段
	if (m_estep == EGameTypeMenu) {
           m_menuselect.OnMouseMove(nFlags, point);
	}
	else {
		m_menubackup.OnMouseMove(nFlags, point);
	}
}
void CGame::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_estep == EGameTypeMenu) {
		m_menuselect.OnLButtonUp(nFlags, point);
	}
	else {
		m_menubackup.OnLButtonUp(nFlags, point);
	}
}

void CGame::SetStep(CGame::EGameType step)
{
	m_estep = step;
	GameInit();
}
void CGame::GameRunDraw()
{
	HDC hdc = ::GetDC(m_hwnd);
	CRect rc;
	GetClientRect(m_hwnd, &rc);

	//双缓冲绘图用
	CDC* dc = CClientDC::FromHandle(hdc);
	CDC m_dcMemory;
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(dc, rc.Width(), rc.Height());
	m_dcMemory.CreateCompatibleDC(dc);
	CBitmap* p0ldBitmap = m_dcMemory.SelectObject(&bmp);

	Graphics gh(m_dcMemory.GetSafeHdc());
	gh.Clear(Color::White);
	gh.ResetClip();

	DrawFps(gh);
	//{
	//	CRect rc;
	//	GetClientRect(m_hwnd, rc);
	//	Gdiplus::Image* img = Image::FromFile(_T("menu_background.png"));
	//	gh.DrawImage(img, rc.left, rc.top, rc.Width(), rc.Height());
	//}
	//
	(this->*m_drawFunc[m_estep])(gh);//画入内存
	//m_menu.Draw(gh);
	//m_menuselect.Draw(gh);


	//{
	//	m_map.Draw(gh);//画出地图
	//	m_player01.Draw(gh);//画出坦克
	//	for (auto& blt : m_lstBullets) {
	//		blt.Draw(gh);
	//	}
	//}

	//将上述图形拷贝到屏幕上面
	::BitBlt(hdc, 0, 0, rc.Width(), rc.Height(), m_dcMemory.GetSafeHdc(), 0, 0,SRCCOPY);
	::ReleaseDC(m_hwnd, hdc);
	return;
}

//选择阶段
void CGame::GameRunDrawMenu(Graphics& gh)
{
	m_menuselect.Draw(gh);
}

//人机大战：菜单阶段
void CGame::GameRunDrawOne2BotMenu(Graphics& gh)
{
	m_menu.Draw(gh);//画背景
	m_keymenu01.Draw(gh);//画菜单
}

//人机大战
void CGame::GameRunDrawOne2Bot(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_bot.Draw(gh);
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
}

//人机大战结束
void CGame::GameRunDrawOne2BotEnd(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_bot.Draw(gh);
	DrawFps(gh);

	if (m_player01.IsBombEnd() || m_bot.IsBombEnd()) {
		m_estep = EGameTypeMenu;
	}
}

//双人大战菜单阶段
void CGame::GameRunDrawOne2OneMenu(Graphics& gh)
{
	m_menu.Draw(gh);
	m_keymenu01.Draw(gh);
	m_keymenu02.Draw(gh);
}

//双人大战
void CGame::GameRunDrawOne2One(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_player02.Draw(gh);

	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
}
//双人大战结束
void CGame::GameRunDrawOne2OneEnd(Graphics& gh)
{
	m_menubackup.Draw(gh);
	m_map.Draw(gh);
	m_player01.Draw(gh);
	m_player02.Draw(gh);
	for (auto b : m_lstBullets) {
		b.Draw(gh);
	}
	DrawFps(gh);
	if (m_player01.IsBombEnd() || m_player02.IsBombEnd()) {
		m_estep = EGameTypeMenu;
	}
}
void CGame::GameRunLogic()
{
	(this->*m_logicFunc[m_estep])();
//#define KEYDOWN(vk) (GetAsyncKeyState(vk) & 0x8000)
//	{
//		if (KEYDOWN(VK_LEFT))
//		{
//			m_player01.RotateLeft();
//		}
//		if (KEYDOWN(VK_RIGHT))
//		{
//			m_player01.RotateRight();
//		}
//		if (KEYDOWN(VK_UP))
//		{
//			//坦克撞墙检测
//			{
//				if (m_map.IsHitTheWall(m_player01, true)) {
//					m_player01.ChangeDirection(true);
//				}
//				else {
//					m_player01.Forward();
//				}
//			}
//		}
//		if (KEYDOWN(VK_DOWN))
//		{
//			if (m_map.IsHitTheWall(m_player01, false)) {
//				m_player01.ChangeDirection(true);
//			}
//			else {
//				m_player01.Backward();
//			}
//			
//		}
//		//if (KEYDOWN(VK_LEFT))
//		//{
//		//	m_player01.RotateLeft();
//		//}
//		if (KEYDOWN('M'))
//		{
//			CBullet blt;
//				if (m_player01.Fire(blt)) {
//					m_lstBullets.push_back(blt);
//				}
//		}
//		//子弹撞墙处理
//	}
//	for (auto& blt : m_lstBullets) {
//		m_map.HitWallProcess(blt);
//		blt.Move();
//		if (m_player01.IsHitted(blt));
//		{
//			m_player01.Bomb();
//		}
//		break;
//	}
//	//移除超时的子弹
//	{
//		auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(),
//			[](CBullet& blt)->bool {return blt.IsTimeout(); });
//
//		for (auto it = itRemove; it != m_lstBullets.end(); ++it) {
//			it->SetActive(false);
//			it->GetOwner()->AddBullet(*it);
//		}
//		//从本地删除子弹
//		m_lstBullets.erase(itRemove, m_lstBullets.end());
//	}
}

//选择阶段的逻辑处理
void CGame::GameRunLogicOnMenu()
{

}

//人机大战菜单阶段逻辑处理
void CGame::GameRunLogicOnOne2BotMenu()
{
	if (KEYDOWN('M'))
	{
		m_keymenu01.SetStop();
	}
	if (m_keymenu01.GetStop()) {
		SetStep(EGameTypeOne2Bot);
	}
}

//人机大战
void CGame::GameRunLogicOnOne2Bot()
{
	RemoveTimeoutBullets();
	for (auto& blt : m_lstBullets) {
		if (m_bot.IsHitted(blt)) {
			m_bot.Bomb();
			m_estep = EGameTypeOne2BotEnd;
			blt.SetActive(false);
		}
		if (m_player01.IsHitted(blt)) {
			m_player01.Bomb();
			m_estep = EGameTypeOne2BotEnd;
			blt.SetActive(false);
		}
		break;
	}
	ProcessHitBullets();
	AI();
	//按键处理
	{
		if (KEYDOWN(VK_LEFT))
		{
			m_player01.RotateLeft();
		}
		if (KEYDOWN(VK_RIGHT))
		{
			m_player01.RotateRight();
		}
		if (KEYDOWN(VK_UP))
		{
			//坦克撞墙检测
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true);
				}
				else {
					m_player01.Forward();
				}
			}
		}
		if (KEYDOWN(VK_DOWN))
		{
			if (m_map.IsHitTheWall(m_player01, false)) {
				m_player01.ChangeDirection(true);
			}
			else {
				m_player01.Backward();
			}

		}
		//if (KEYDOWN(VK_LEFT))
		//{
		//	m_player01.RotateLeft();
		//}
		if (KEYDOWN('M'))
		{
			CBullet blt;
			if (m_player01.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		if (KEYDOWN('I')) {
			//机器人，玩家一所在的位置
			int startX, startY, targetX, targetY;
				if (!m_map.FindObjPosition(m_bot, startX, startY)|| !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		float fDirNext = 0;//机器人下一步的方向
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetX)) {
			return;
		}
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startX);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		if (!rc.Contains(ptTankCenter)) {
			m_bot.Forward();
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);
			m_bot.Forward();
		}
		}
		
	}
}

//人机大战结束的游戏逻辑
void CGame::GameRunLogicOnOne2BotEnd()
{
	RemoveTimeoutBullets();
	ProcessHitBullets();

}



//双人大战菜单阶段游戏逻辑
void CGame::GameRunLogicOnOne2OneMenu()
{
	if (KEYDOWN('M')) {//按下M键停止动画
		m_keymenu01.SetStop();
	}
	if (KEYDOWN('Q')) {//按下Q键停止动画
		m_keymenu02.SetStop();
	}
	//如果都按下了。则开始游戏
	if (m_keymenu01.GetStop() && m_keymenu02.GetStop()) {
		SetStep(EGameTypeOne2One);
	}
}

//双人大战游戏逻辑
void CGame::GameRunLogicOnOne2One()
{
	//按键处理
	{
		if (KEYDOWN(VK_LEFT))
		{
			m_player01.RotateLeft();
		}
		if (KEYDOWN(VK_RIGHT))
		{
			m_player01.RotateRight();
		}
		if (KEYDOWN(VK_UP))
		{
			//坦克撞墙检测
			{
				if (m_map.IsHitTheWall(m_player01, true)) {
					m_player01.ChangeDirection(true);
				}
				else {
					m_player01.Forward();
				}
			}
		}
		if (KEYDOWN(VK_DOWN))
		{
			if (m_map.IsHitTheWall(m_player01, false)) {
				m_player01.ChangeDirection(false);
			}
			else {
				m_player01.Backward();
			}

		}
		//if (KEYDOWN(VK_LEFT))
		//{
		//	m_player01.RotateLeft();
		//}
		if (KEYDOWN('M'))
		{
			CBullet blt;
			if (m_player01.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		//玩家二
		if (KEYDOWN('A')) {
			m_player02.RotateLeft();
		}
		if (KEYDOWN('D')) {
			m_player02.RotateRight();
		}
		if (KEYDOWN('W')) {
			//坦克撞墙检测
			{
				if (m_map.IsHitTheWall(m_player02, true)) {
					m_player02.ChangeDirection(true);
				}
				else {
					m_player02.Forward();
				}
			}
		}
		if (KEYDOWN('S')) {
			//坦克撞墙检测
			{
				if (m_map.IsHitTheWall(m_player02, false)) {
					m_player02.ChangeDirection(false);
				}
				else {
					m_player02.Backward();
				}
			}
		}
		if (KEYDOWN('Q')) {
			CBullet blt;
			if (m_player02.Fire(blt)) {
				m_lstBullets.push_back(blt);
			}
		}
		if (KEYDOWN('Z')) {
			if (m_map.IsCanKillTarget(m_player01, m_player02)) {
				AfxMessageBox(_T("可以打到"));
			}
		}
	}
	RemoveTimeoutBullets();

	//检查子弹是否击中坦克：击中要使坦克爆炸（游戏结束）
	for (auto& blt : m_lstBullets) {
		if (!blt.IsActive()) {
			continue;
		}
		if (m_player01.IsHitted(blt)) {
			m_player01.Bomb();
			m_estep = EGameTypeOne2OneEnd;
			blt.SetActive(false);
		}
		if (m_player02.IsHitted(blt)) {
			m_player02.Bomb();
			m_estep = EGameTypeOne2OneEnd;
			blt.SetActive(false);
		}
	}

	ProcessHitBullets();
}

//双人大战结束
void CGame::GameRunLogicOnOne2OneEnd()
{
	RemoveTimeoutBullets();
	ProcessHitBullets();
}


bool CGame::GameInit()
{
	srand(GetTickCount64());//可以调用Gettickcount函数以避免出现重复的随机数结果
		return (this->*m_initFunc[m_estep])();
}

bool CGame::GameInitMenu()
{
	return true;
}
//人机大战菜单阶段初始化
bool CGame::GameInitOne2BotMenu()
{
	RECT rc;
	GetWindowRect(m_hwnd, &rc);
	PointF pt;
	pt.X = (rc.left + (rc.right - rc.left) / 2.0f);
	pt.Y = (rc.top + (rc.bottom - rc.top) / 2.0f);
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);
	return true;
}

//人机大战初始化
bool CGame::GameInitOne2Bot()
{
	for(; ;)
	{
		m_map.LoadMap();
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整玩家1位置失败"));
			}
			else {
				//设置玩家1的中心点，让玩家1处于地图格子的正中间位置
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		//机器人
		{
			m_bot = CBot(0, 0, _T("tank_bot.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter))
			{
				AfxMessageBox(_T("调整Bot位置失败"));
			}
			else
			{
				m_bot.SetCenterPoint(ptCenter);
			}
		}
		//子弹
		m_lstBullets.clear();
		//判断是否合法
		{
			int startX, startY, targetX, targetY;
			m_map.FindObjPosition(m_bot, startX, startY);
			m_map.FindObjPosition(m_player01, targetX, targetY);
			//if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY));	
			//{
			//	AfxMessageBox(_T("人机大战初始化获取坦克的位置发生错误"));            
			//}
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty())
			{
				break;
			}
		}
	}
	return true;
}

//人机大战结束初始化
bool CGame::GameInitOne2BotEnd()
{
	return true;
}

//双人大战菜单初始化
bool CGame::GameInitOne2OneMenu()
{
	RECT rc;
	GetWindowRect(m_hwnd, &rc);
	PointF pt;
	pt.X = rc.left +m_keymenu01.GetRect().Width / 2.0f+100;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);

	pt.X = rc.left + m_keymenu01.GetRect().Width / 2.0f - 100;
	pt.Y = rc.top + (rc.bottom - rc.top) / 2.0f;
	m_keymenu01.SetCenterPoint(pt);
	m_keymenu01.SetStop(false);
	return true;
}

//双人大战初始化
bool CGame::GameInitOne2One()
{
	for (;;) {
		m_map.LoadMap();
		{
			m_player01 = CPlayer(0, 0, _T("tank_player1.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整玩家1位置失败"));
			}
			else {
				//设置玩家1的中心点，让玩家1处于地图格子的正中间位置
				m_player01.SetCenterPoint(ptCenter);
			}
		}
		//玩家2
		{
			m_player02 = CPlayer(0, 0, _T("tank_player2.png"));
			PointF ptCenter;
			if (!m_map.FindRandomPosition(ptCenter)) {
				AfxMessageBox(_T("调整玩家02位置失败"));
			}
			else {
				//设置玩家1的中心点，让玩家1处于地图格子的正中间位置
				m_player02.SetCenterPoint(ptCenter);
			}
		}
		//子弹
		m_lstBullets.clear();
		//判断是否合法
		{
			int startX, startY, targetX, targetY;
			m_map.FindObjPosition(m_player02, startX, startY);
			m_map.FindObjPosition(m_player01, targetX, targetY);
			//if (!m_map.FindObjPosition(m_player02, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY));
			//{
			//	AfxMessageBox(_T("双人大战初始化获取坦克的位置发生错误"));
			//}
			//判断两个玩家是否可以联通
			VPath path;
			m_map.FindPath(startX, startY, targetX, targetY, path);
			if (!path.empty())
			{
				break;
			}
		}
	}
	return true;
}

//双人大战结束初始化
bool CGame::GameInitOne2OneEnd()
{
	return true;
}

//画fps
void CGame::DrawFps(Graphics& gh)
{
	static int fps = 0;
	m_fps++;
	static DWORD dwLast = GetTickCount64();
	if (GetTickCount64() - dwLast >= 1000)
	{
		fps = m_fps;
		m_fps = 0;
		dwLast = GetTickCount64();
	}
	//输出fps
	{
		CString s;
		s.Format(_T("FPS:%d"), fps);
		SolidBrush brush(Color(0x00, 0x00, 0xFF));//颜色为红色
		Gdiplus::Font font(_T("宋体"), 10.0);//字体
		CRect rc;
		::GetClientRect(m_hwnd, &rc);
		//文字的位置，在窗口的右上角显示
		PointF origin(static_cast<float>(rc.right - 50), static_cast<float>(rc.top + 2));//把整数直接转为浮点型
		gh.DrawString(s.GetString(), -1, &font, origin, &brush);
	}
}

//移除超时的子弹
void CGame::RemoveTimeoutBullets()
{
	auto itRemove = std::remove_if(m_lstBullets.begin(), m_lstBullets.end(), [](CBullet& blt)->bool {return blt.IsTimeout(); });

	//把子弹移除，并且给对应的坦克增加子弹
	for (auto it = itRemove; it != m_lstBullets.end(); ++it)
	{
		it->SetActive(false);
		it->GetOwner()->AddBullet(*it);
	}
	m_lstBullets.erase(itRemove, m_lstBullets.end());
}

//子弹运动的维护
void CGame::ProcessHitBullets()
{
	for (auto& blt : m_lstBullets) {
		m_map.HitWallProcess(blt);
		blt.Move();
	}
}

//维护电脑自动 寻路攻击
void CGame::AI()
{
	static CGameTimer acTimer(-1, 150);
	if (acTimer.IsTimeval()) {
		int startX, startY, targetX, targetY;
		if (!m_map.FindObjPosition(m_bot, startX, startY) || !m_map.FindObjPosition(m_player01, targetX, targetY)) {
			return;
		}
		float fDirNext = 0;
		if (!m_map.FindNextDirection(&fDirNext, startX, startY, targetX, targetY)) {
			return;
		}
		PointF ptTankCenter = m_bot.GetCenterPoint();
		PointF ptAreaCenter = m_map.GetElementAreaCenter(startX, startY);
		RectF rc(ptAreaCenter.X - 5, ptAreaCenter.Y - 5, 10, 10);

		if (!rc.Contains(ptTankCenter)) {
			m_bot.Forward();
			return;
		}
		else {
			m_bot.SetDirection(fDirNext);
			float dir;
			if (m_map.IsCanKillTarget(m_bot, m_player01, &dir)) {
				CBullet blt;
				if (m_bot.Fire(blt)) {
					m_lstBullets.push_back(blt);
				}
				return;
			}
			m_bot.Forward();
		}
	}
}