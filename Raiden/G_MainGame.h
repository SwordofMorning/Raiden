#pragma once

#include <opencv.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <random>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")
#include <mmsystem.h>
#include "A_Actor.h"
#include "A_PlayerFighter.h"
#include "G_GameScene.h"
#include "A_Enemy.h"
#include "A_EnemyBullets.h"
#include "A_ScoreRank.h"

extern const std::pair<int, int> BackGroundScale;
extern const std::pair<int, int> PlayerFighterScale;
extern const std::pair<int, int> MouseMoveUpDownLimit;
extern const std::pair<int, int> MouseMoveLeftRightLimit;

/*=== 游戏主控类 ===*/
class G_MainGame
{
private:
	/*--- 游戏变量 ---*/
	cv::Mat m_GameMainMenu;											//游戏主菜单界面
	cv::Mat m_GameEndMenu;											//游戏通关菜单
	cv::Mat m_GameContinueMenu;										//关卡完成菜单
	cv::Mat m_GameBackground;										//游戏背景

	/*--- 数组 ---*/
	std::vector<G_GameScene> m_VecGameScenes;						//游戏关卡
	std::vector<std::string> m_VecEnemyImgPath;						//敌人图片数组

	/*--- 玩家角色 ---*/
	A_PlayerFighter m_PlayerFighter;								//玩家战机

	/*--- UI ---*/
	int m_score;													//得分
	A_ScoreRank m_ScoreRank;										//得分等级
	A_Actor m_BossComing_1;											//BossComing
	A_Actor m_BossComing_2;
	A_Actor m_BossHealth;											//Boss血量UI
	cv::Point m_BossHealthBegin;									//Boss血量起点
	cv::Point m_BossHealthEnd;										//Boss血量终点
public:
	G_MainGame(const std::string& p_GameMainMenu_Path = ".\\Source\\Re_Menu\\Raiden_MainMenu.png",
		const std::string& p_GameEndMenu_Path = ".\\Source\\Re_Menu\\Raiden_End.png",
		const std::string& p_GameContinueMenu_Path = ".\\Source\\Re_Menu\\Raiden_Comtinue.png",
		const std::string& p_GameBackGround_Path1 = ".\\Source\\Re_BackGround\\BackGround1.png",
		const std::string& p_GameBackGround_Path2 = ".\\Source\\Re_BackGround\\BackGround2.png",
		const std::string& p_GameBackGround_Path3 = ".\\Source\\Re_BackGround\\BackGround3.png",
		const std::string& p_GameBackGround_Path4 = ".\\Source\\Re_BackGround\\BackGround4.png",
		const std::string& p_GameBackGround_Path5 = ".\\Source\\Re_BackGround\\BackGround5.png" ,
		const std::string& p_BossImgPath_1 = ".\\Source\\Re_Boss\\Boss_01.png",
		const std::string& p_BossImgPath_2 = ".\\Source\\Re_Boss\\Boss_02.png", 
		const std::string& p_BossImgPath_3 = ".\\Source\\Re_Boss\\Boss_03.png", 
		const std::string& p_BossImgPath_4 = ".\\Source\\Re_Boss\\Boss_04.png", 
		const std::string& p_BossImgPath_5 = ".\\Source\\Re_Boss\\Boss_05.png" );

	bool PlayerFighterMove();												//玩家战机移动
			
	bool PlayerFighterFire();												//玩家战机开火

	void GameLoop();														//游戏循环

	void GameScene(int p_SceneNum);											//游戏关卡

	void GameStartMainMenu();												//游戏开始菜单

	void GameContinueMenu();												//关卡结束游戏继续

	void GameEndMenu();														//游戏结束

	friend void PlayerFighterMouseEvent(int p_event, int p_x, int p_y, int flag, void* ustc);

	/*--- 辅助功能 ---*/
	int RandomNum(const int& LowerLimmit, const int& UpperLimmit);			//随机数

	/*--- UI ---*/
	void UI_ScoreRank();													//得分函数
};


