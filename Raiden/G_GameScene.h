#pragma once

#include <opencv.hpp>
#include <list>
#include "A_Enemy.h"
#include "A_Boss.h"

/*=== 游戏关卡类 ===*/
class G_GameScene
{
public:
	/*--- 背景 ---*/
	cv::Mat m_ImgGameBackScene;									//游戏背景图
	cv::Mat m_ImgGameBackSceneClone;							//游戏背景图副本

	/*--- 一般敌人 ---*/
	int m_NumberofEnemy;										//敌人数量 => 敌人只有外观的变化		
	/*
	敌人逻辑：在MinGame中反复生成，直到达到敌人数量，之后出现boss
	*/

	/*---Boss ---*/
	A_Boss m_Boss;												//关卡Boss
public:
	G_GameScene(const std::string& p_GameBackGround_Path,
		const int& p_NumberofEnemy,
		const std::string& p_BossImgPath,
		const int& p_BossHealth );
};

