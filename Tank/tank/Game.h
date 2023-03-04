#pragma once
#include "GameMenuBackground.h"
#include "GameMenuPanel.h"
#include "TankEntry.h"
#include "Bot.h"
#include "Bullet.h"
#include "Player.h"
#include "GameMap.h"
#include "Wall.h"
#include "Bullet.h"
#include "Player.h"
#include "Bot.h"
#include "GameMap.h"
#include "GameMenuPanel.h"
#include "GameMenuPanel2.h"
#include "GameMenuBackground.h"
#include "KeyMenuPlayer01.h"
#include "KeyMenuPlayer02.h"
class CGame
{
public:
	CGame();
	~CGame();
	void SetHandle(HWND hwnd);
	bool EnterFrame(DWORD dwTime);
	void OnMouseMove(UINT nFlags, CPoint point);//处理鼠标移动事件
	void OnLButtonUp(UINT nFlags, CPoint point);//处理左键抬起事件
	//当前游戏所处的阶段
	enum EGameType {
		EGameTypeMenu = 0,
		EGameTypeOne2BotMenu,//1
		EGameTypeOne2Bot,//2
		EGameTypeOne2BotEnd,
		EGameTypeOne2OneMenu,
		EGameTypeOne2One,
		EGameTypeOne2OneEnd,
		EGameTypeCount,//7
	};
	//设置当前游戏所处的阶段，并根据步骤初始化
	void SetStep(CGame::EGameType step);
private:
	HWND m_hwnd;//窗口
	//游戏初始化
	bool GameInit();
	bool GameInitMenu();
	bool GameInitOne2BotMenu();
	bool GameInitOne2Bot();
	bool GameInitOne2BotEnd();
	bool GameInitOne2OneMenu();
	bool GameInitOne2One();
	bool GameInitOne2OneEnd();
	//定义一个函数指针数组
	bool (CGame::* m_initFunc[EGameTypeCount])() = {
		&CGame::GameInitMenu,
		&CGame::GameInitOne2BotMenu,
		&CGame::GameInitOne2Bot,
		&CGame::GameInitOne2BotEnd,
		&CGame::GameInitOne2OneMenu,
		&CGame::GameInitOne2One,
		&CGame::GameInitOne2OneEnd
	};
	//游戏绘图处理，负责绘画游戏钟的对象
	void GameRunDraw();
	void GameRunDrawMenu(Graphics &gh);
	void GameRunDrawOne2BotMenu(Graphics& gh);
	void GameRunDrawOne2Bot(Graphics& gh);
	void GameRunDrawOne2BotEnd(Graphics& gh);
	void GameRunDrawOne2OneMenu(Graphics& gh);
	void GameRunDrawOne2One(Graphics& gh);
	void GameRunDrawOne2OneEnd(Graphics& gh);
	void(CGame::* m_drawFunc[EGameTypeCount])(Graphics&) = {
		&CGame::GameRunDrawMenu,
		&CGame::GameRunDrawOne2BotMenu,
		&CGame::GameRunDrawOne2Bot,
		&CGame::GameRunDrawOne2BotEnd,
		&CGame::GameRunDrawOne2OneMenu,
		&CGame::GameRunDrawOne2One,
		&CGame::GameRunDrawOne2OneEnd
	};
	//游戏逻辑处理，维护子弹，机器人，玩家坦克的状态
	void GameRunLogic();
	void GameRunLogicOnMenu();//选择阶段
	void GameRunLogicOnOne2BotMenu();//人机大战菜单
	void GameRunLogicOnOne2Bot();//人机大战
	void GameRunLogicOnOne2BotEnd();//人机大站结束
	void GameRunLogicOnOne2OneMenu();//双人大战菜单
	void GameRunLogicOnOne2One();//双人大战
	void GameRunLogicOnOne2OneEnd();//双人大战结束
	void(CGame::* m_logicFunc[EGameTypeCount])() = {
		&CGame::GameRunLogicOnMenu,
		&CGame::GameRunLogicOnOne2BotMenu,
		&CGame::GameRunLogicOnOne2Bot,
		&CGame::GameRunLogicOnOne2BotEnd,
		&CGame::GameRunLogicOnOne2OneMenu,
		&CGame::GameRunLogicOnOne2One,
		&CGame::GameRunLogicOnOne2OneEnd
	};
private:
	void RemoveTimeoutBullets();
	void ProcessHitBullets();
	void AI();
	void DrawFps(Graphics& gh);
private:
	int m_fps{ 0 };
	EGameType m_estep{ EGameTypeMenu };
	CPlayer m_player01;
	CPlayer m_player02;
	CBot m_bot;
	std::list<CBullet>m_lstBullets;
	CGameMap m_map{ 10,10,780,580 };
	CGameMenuPanel m_menuselect;
	CGameMenuBackground m_menu;
	CGameMenuPanel2 m_menubackup;//返回菜单
	CKeyMenuPlayer01 m_keymenu01;
	CKeyMenuPlayer02 m_keymenu02;


	//CGameMenuPanel m_menuSelect;
	//CGameMenuBackground m_menu;
	//游戏的绘图
	//void DrawFps(Graphics& gh);
	//	int m_fps{ 0 };

	//CPlayer m_player01{ 100,100,_T("tank_player1.png") };
	//CPlayer m_player02{ 200,100,_T("tank_player2.png") };
	//CBot m_bot{ 300,200,_T("tank_bot.png") };
	//std::list<CBullet>m_lstBullets;//声明一个列表来保存已经发射出来的子弹
	//CGameMap m_map{ 10,10,780,580 };//初始化了一个地图对象
	//bool CGame::GameInitOne2Bot();//游戏初始化，人机大战
};

