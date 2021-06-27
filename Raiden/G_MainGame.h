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

/*=== ��Ϸ������ ===*/
class G_MainGame
{
private:
	/*--- ��Ϸ���� ---*/
	cv::Mat m_GameMainMenu;											//��Ϸ���˵�����
	cv::Mat m_GameEndMenu;											//��Ϸͨ�ز˵�
	cv::Mat m_GameContinueMenu;										//�ؿ���ɲ˵�
	cv::Mat m_GameBackground;										//��Ϸ����

	/*--- ���� ---*/
	std::vector<G_GameScene> m_VecGameScenes;						//��Ϸ�ؿ�
	std::vector<std::string> m_VecEnemyImgPath;						//����ͼƬ����

	/*--- ��ҽ�ɫ ---*/
	A_PlayerFighter m_PlayerFighter;								//���ս��

	/*--- UI ---*/
	int m_score;													//�÷�
	A_ScoreRank m_ScoreRank;										//�÷ֵȼ�
	A_Actor m_BossComing_1;											//BossComing
	A_Actor m_BossComing_2;
	A_Actor m_BossHealth;											//BossѪ��UI
	cv::Point m_BossHealthBegin;									//BossѪ�����
	cv::Point m_BossHealthEnd;										//BossѪ���յ�
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

	bool PlayerFighterMove();												//���ս���ƶ�
			
	bool PlayerFighterFire();												//���ս������

	void GameLoop();														//��Ϸѭ��

	void GameScene(int p_SceneNum);											//��Ϸ�ؿ�

	void GameStartMainMenu();												//��Ϸ��ʼ�˵�

	void GameContinueMenu();												//�ؿ�������Ϸ����

	void GameEndMenu();														//��Ϸ����

	friend void PlayerFighterMouseEvent(int p_event, int p_x, int p_y, int flag, void* ustc);

	/*--- �������� ---*/
	int RandomNum(const int& LowerLimmit, const int& UpperLimmit);			//�����

	/*--- UI ---*/
	void UI_ScoreRank();													//�÷ֺ���
};


